#include "jsnparse.h"
#include "string.h"
#include "stdlib.h"
#include "jsmn.h"
#include "stdio.h"

#define MAX_TOKENS 256
#define MAX_TOKEN_KEYWORD_SIZE 20

//Jump straight to the Json portion skipping the HTTP content
static void jsnparse_getStartOfJson(LPSTR response, DWORD responseLength, LPSTR * startPosition, DWORD * lengthOfJson){
    DWORD index;

    for(index = 0; index < responseLength; index++){
        if(response[index] == '{'){
            *startPosition = response + index;
            break;
        }
    }

    *lengthOfJson = responseLength - index;
}

static char * jsnparse_extractStringOfThisToken(LPSTR startOfJson, jsmntok_t * currentToken){
    
    int tokenStartPosition = currentToken->start;
    int tokenSize = currentToken->end - tokenStartPosition;
    char * output = NULL;

    if(tokenSize <= 0){
        return output;
    }

    output = calloc(tokenSize + 1, sizeof(char));

    if(output != NULL){
        _fmemcpy(output, startOfJson + tokenStartPosition, tokenSize);
    }
   

    return output;
}

void jsnparse_parseMessageList(LPSTR response, DWORD length, MessageList * list){
    jsmn_parser parser;
    jsmntok_t tokens[MAX_TOKENS];
    int index;
    LPSTR startOfJson;
    DWORD lengthOfJson;

    char * currentTokenString;
    char * currentTokenStringp2;

    jsnparse_getStartOfJson(response, length, &startOfJson, &lengthOfJson);

    jsmn_init(&parser);
    jsmn_parse(&parser, startOfJson, lengthOfJson, tokens, MAX_TOKENS);

    //First pass to determine number of channels there are
    for(index = 0; index < MAX_TOKENS; index++){

        currentTokenString = jsnparse_extractStringOfThisToken(startOfJson, &tokens[index]);

        if(strcmp("text", currentTokenString) == 0){

            //Verify that the channel ID and name does not exceed the tokens we have
            if(((index + 1) < MAX_TOKENS) && ((index + 3) < MAX_TOKENS)){

                //Make sure [index + 2] token is "user" as "text" and "user" must come in a pair
                currentTokenStringp2 = jsnparse_extractStringOfThisToken(startOfJson, &tokens[index + 2]);

                if(strcmp("user", currentTokenStringp2) == 0){

                    list->messages = (Message * ) realloc(list->messages, (list->numMessages + 1) * sizeof(Message));

                    list->messages[list->numMessages].message = jsnparse_extractStringOfThisToken(startOfJson, &tokens[index + 1]);
                    list->messages[list->numMessages].userID = jsnparse_extractStringOfThisToken(startOfJson, &tokens[index + 3]);

                    list->numMessages++;
                }

                free(currentTokenStringp2);
                
            }

        }
        free(currentTokenString);
    }
}



void jsnparse_freeMessagesList(MessageList * list){
    int index;

    for(index = 0; index < list->numMessages; index++){
        free(list->messages[index].message);
        free(list->messages[index].userID);
    }

    free(list->messages);
}


void jsnparse_parseChannelList(LPSTR response, DWORD length, ChannelList * list){
    jsmn_parser parser;
    jsmntok_t tokens[MAX_TOKENS];
    int index;
    LPSTR startOfJson;
    DWORD lengthOfJson;

    int tokenStartPosition;
    int tokenSize;
    jsmntok_t currentToken;
    char currentTokenString[MAX_TOKEN_KEYWORD_SIZE];
    int numberOfChannels = 0;
    int channelIndex = 0;

    jsnparse_getStartOfJson(response, length, &startOfJson, &lengthOfJson);

    jsmn_init(&parser);
    jsmn_parse(&parser, startOfJson, lengthOfJson, tokens, MAX_TOKENS);

    //First pass to determine number of channels there are
    for(index = 0; index < MAX_TOKENS; index++){
        currentToken = tokens[index];
        tokenStartPosition = currentToken.start;
        tokenSize = currentToken.end - tokenStartPosition;

        if(tokenSize <= 0){
            continue;
        }

        if(tokenSize > MAX_TOKEN_KEYWORD_SIZE){
            continue;
        }

        memset(currentTokenString, 0, MAX_TOKEN_KEYWORD_SIZE);
        _fmemcpy(currentTokenString, startOfJson + tokenStartPosition, tokenSize);

        //We found the start of a nested json for a channel
        if(strcmp("id", currentTokenString) == 0){

            //Verify that the channel ID and name does not exceed the tokens we have
            if(((index + 1) < MAX_TOKENS) && ((index + 3) < MAX_TOKENS)){
                numberOfChannels++;
            }

        }
    }

    list->channels = (Channel * ) malloc(numberOfChannels * sizeof(Channel));
    list->numChannels = numberOfChannels;


    for(index = 0; index < MAX_TOKENS; index++){
        currentToken = tokens[index];
        tokenStartPosition = currentToken.start;
        tokenSize = currentToken.end - tokenStartPosition;

        if(tokenSize <= 0){
            continue;
        }

        if(tokenSize > MAX_TOKEN_KEYWORD_SIZE){
            continue;
        }

        memset(currentTokenString, 0, MAX_TOKEN_KEYWORD_SIZE);
        _fmemcpy(currentTokenString, startOfJson + tokenStartPosition, tokenSize);

        //We found the start of a nested json for a channel
        if(strcmp("id", currentTokenString) == 0){

            //Verify that the channel ID and name does not exceed the tokens we have
            if(((index + 1) < MAX_TOKENS) && ((index + 3) < MAX_TOKENS)){
                
                // Copy the data to the return structure
                list->channels[channelIndex].channelID = (char *)calloc((tokens[index + 1].end - tokens[index + 1].start + 1), sizeof(char));
                _fmemcpy(list->channels[channelIndex].channelID, startOfJson + tokens[index + 1].start, tokens[index + 1].end - tokens[index + 1].start);
                
                list->channels[channelIndex].channelName = (char *)calloc((tokens[index + 3].end - tokens[index + 3].start + 1), sizeof(char));
                _fmemcpy(list->channels[channelIndex].channelName, startOfJson + tokens[index + 3].start, tokens[index + 3].end - tokens[index + 3].start);

                channelIndex++;

            }

        }
    }
}


void jsnparse_freeChannelList(ChannelList * list){
    int index;

    for(index = 0; index < list->numChannels; index++){
        free(list->channels[index].channelName);
        free(list->channels[index].channelID);
    }

    free(list->channels);
}
#include "jsnparse.h"
#include "string.h"
#include "stdlib.h"
#include "jsmn.h"
#include "stdio.h"

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

static LPSTR jsnparse_extractThisTokenAndNextFew(LPSTR jsonStart, DWORD length, char * keyString, jsmntok_t * tokens, int totalTokens){
    
    jsmn_parser parser;
    
    LPSTR firstInstance;
    firstInstance = _fstrstr(jsonStart, keyString);

    if(firstInstance != NULL){

        //To protect against the case that the first instance has exceed the bounds. Possible if the memory is not cleared.
        if((DWORD) (firstInstance - jsonStart) > length){
            return NULL;
        }

        jsmn_init(&parser);
        jsmn_parse(&parser, firstInstance, length - (firstInstance - jsonStart), tokens, totalTokens);
    }

    return firstInstance;
}

void jsnparse_parseMessageList(LPSTR response, DWORD length, MessageList * list, int maxMessagesToParse){

    LPSTR startOfJson;
    DWORD lengthOfJson;

    LPSTR startOfNextSubstring;
    char * tokenString;
    jsmntok_t tokens[4];

    jsnparse_getStartOfJson(response, length, &startOfJson, &lengthOfJson);

    startOfNextSubstring = startOfJson;
    list->numMessages = 0;

    while((startOfNextSubstring = jsnparse_extractThisTokenAndNextFew(startOfNextSubstring, lengthOfJson - (startOfNextSubstring - startOfJson), "\"text\":", tokens, 4)) != NULL){

        if(startOfNextSubstring == NULL){
            break;
        }

        if(list->numMessages >= maxMessagesToParse){
            break;
        }

        tokenString = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[2]);

        if(strcmp("user", tokenString) == 0){

            list->messages = (Message * ) realloc(list->messages, (list->numMessages + 1) * sizeof(Message));

            list->messages[list->numMessages].message = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[1]);
            list->messages[list->numMessages].userID = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[3]);

            list->numMessages++;
        }

        //Start the next iteration away from the current position. +1 is sufficient to not include the current token
        startOfNextSubstring = startOfNextSubstring + 1;

        free(tokenString);
    }
}

void jsnparse_freeMessagesList(MessageList * list){
    int index;

    for(index = 0; index < list->numMessages; index++){
        free(list->messages[index].message);
        free(list->messages[index].userID);
    }

    free(list->messages);
    list->messages = NULL;
    list->numMessages = 0;
}

void jsnparse_parseChannelList(LPSTR response, DWORD length, ChannelList * list){

    LPSTR startOfJson;
    DWORD lengthOfJson;

    LPSTR startOfNextSubstring;
    char * tokenString;
    jsmntok_t tokens[4];

    jsnparse_getStartOfJson(response, length, &startOfJson, &lengthOfJson);

    startOfNextSubstring = startOfJson;
    list->numChannels = 0;

    while((startOfNextSubstring = jsnparse_extractThisTokenAndNextFew(startOfNextSubstring, lengthOfJson - (startOfNextSubstring - startOfJson), "\"id\":", tokens, 4)) != NULL){

        if(startOfNextSubstring == NULL){
            break;
        }

        tokenString = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[2]);

        if(strcmp("name", tokenString) == 0){

            list->channels = (Channel * ) realloc(list->channels, (list->numChannels + 1) * sizeof(Channel));

            list->channels[list->numChannels].channelID = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[1]);
            list->channels[list->numChannels].channelName = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[3]);

            list->numChannels++;
        }

        //Start the next iteration away from the current position. +1 is sufficient to not include the current token
        startOfNextSubstring = startOfNextSubstring + 1;

        free(tokenString);
    }
}

void jsnparse_freeChannelList(ChannelList * list){
    int index;

    for(index = 0; index < list->numChannels; index++){
        free(list->channels[index].channelName);
        free(list->channels[index].channelID);
    }

    free(list->channels);
    list->channels = NULL;
    list->numChannels = 0;
}

void jsnparse_parseUserList(LPSTR response, DWORD length, UserList * list){

    LPSTR startOfJson;
    DWORD lengthOfJson;

    LPSTR startOfNextSubstring;
    char * tokenString;
    jsmntok_t tokens[6];

    jsnparse_getStartOfJson(response, length, &startOfJson, &lengthOfJson);

    startOfNextSubstring = startOfJson;
    list->numUsers = 0;

    while((startOfNextSubstring = jsnparse_extractThisTokenAndNextFew(startOfNextSubstring, lengthOfJson - (startOfNextSubstring - startOfJson), "\"id\":", tokens, 6)) != NULL){

        if(startOfNextSubstring == NULL){
            break;
        }

        tokenString = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[4]);

        if(strcmp("name", tokenString) == 0){

            list->users = (User * ) realloc(list->users, (list->numUsers + 1) * sizeof(User));

            list->users[list->numUsers].userID = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[1]);
            list->users[list->numUsers].username = jsnparse_extractStringOfThisToken(startOfNextSubstring, &tokens[5]);

            list->numUsers++;
        }

        //Start the next iteration away from the current position. +1 is sufficient to not include the current token
        startOfNextSubstring = startOfNextSubstring + 1;

        free(tokenString);
    }
}

void jsnparse_freeUserList(UserList * list){
    int index;

    for(index = 0; index < list->numUsers; index++){
        free(list->users[index].username);
        free(list->users[index].userID);
    }

    free(list->users);
    list->users = NULL;
    list->numUsers = 0;
}
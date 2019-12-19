#include "jsnparse.h"
#include "windows.h"
#include "..\tstconst.h"
#include <stdlib.h>


#define TEST_CHANNEL0_ID "CPV9L2UJV"
#define TEST_CHANNEL0_NAME "random"

#define TEST_CHANNEL1_ID "CPV9L2VT3"
#define TEST_CHANNEL1_NAME "win31"

#define TEST_CHANNEL2_ID "CQ2NUCLDA"
#define TEST_CHANNEL2_NAME "playground"

#define TEST_CHANNEL3_ID "CQ52U515M"
#define TEST_CHANNEL3_NAME "general"

BOOL test_jsnparse_parseMessageList(){
    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;
    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    MessageList expectedList = {NULL, 7};
    MessageList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    //There are 50 messages in the text file but due to json parsing limitations, we can only see the latest 7.
    expectedList.messages = (Message *) malloc(7 * sizeof(Message));

    expectedList.messages[0].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[0].message, "hello");

    expectedList.messages[1].message = (char *)malloc((strlen("hello retro test!") + 1) * sizeof(char));
    strcpy(expectedList.messages[1].message, "hello retro test!");

    expectedList.messages[2].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[2].message, "hello");

    expectedList.messages[3].message = (char *)malloc((strlen("hello retro test!") + 1) * sizeof(char));
    strcpy(expectedList.messages[3].message, "hello retro test!");   

    expectedList.messages[4].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[4].message, "hello");

    expectedList.messages[5].message = (char *)malloc((strlen("hello retro test!") + 1) * sizeof(char));
    strcpy(expectedList.messages[5].message, "hello retro test!");

    expectedList.messages[6].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[6].message, "hello");


    for(index = 0; index < 7; index++){
        expectedList.messages[index].userID = (char *)malloc((strlen("UQ2NT009J") + 1) * sizeof(char));
        strcpy(expectedList.messages[index].userID, "UQ2NT009J");
    }


    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    outputListText = fopen(".\\mocksvr\\ouconhis.txt", "rb");

    while((read = fgetc(outputListText)) != EOF){
        lpGlobalMemory[dindex] = read;
        dindex++;
    }

    fclose(outputListText);

    jsnparse_parseMessageList(lpGlobalMemory, dindex, &actualList);

    if(expectedList.numMessages == actualList.numMessages){

        for(index = 0; index < expectedList.numMessages; index++){
            if (strcmp (expectedList.messages[index].userID, actualList.messages[index].userID) != 0){
                printf("fail %s\n", expectedList.messages[index].userID);
                testResult = FALSE;
                break;
            }

            if (strcmp (expectedList.messages[index].message, actualList.messages[index].message) != 0){
                printf("fail %s\n", expectedList.messages[index].message);
                testResult = FALSE;
                break;
            }

        }

    } else {
        testResult = FALSE;
        printf("Not enough messages expected %d, got %d\n", expectedList.numMessages, actualList.numMessages);
    }



    jsnparse_freeMessagesList(&expectedList);

    GlobalFreePtr(lpGlobalMemory);

    return testResult;

}


BOOL test_jsnparse_parseChannelList(){

    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;
    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    ChannelList expectedList = {NULL, 4};
    ChannelList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    expectedList.channels = (Channel *) malloc(4 * sizeof(Channel));

    expectedList.channels[0].channelID = (char *)malloc((strlen(TEST_CHANNEL0_ID) + 1) * sizeof(char));
    expectedList.channels[0].channelName = (char *)malloc((strlen(TEST_CHANNEL0_NAME) + 1) * sizeof(char));
    strcpy(expectedList.channels[0].channelID, TEST_CHANNEL0_ID);
    strcpy(expectedList.channels[0].channelName, TEST_CHANNEL0_NAME);

    expectedList.channels[1].channelID = (char *)malloc((strlen(TEST_CHANNEL1_ID) + 1) * sizeof(char));
    expectedList.channels[1].channelName = (char *)malloc((strlen(TEST_CHANNEL1_NAME) + 1) * sizeof(char));
    strcpy(expectedList.channels[1].channelID, TEST_CHANNEL1_ID);
    strcpy(expectedList.channels[1].channelName, TEST_CHANNEL1_NAME);

    expectedList.channels[2].channelID = (char *)malloc((strlen(TEST_CHANNEL2_ID) + 1) * sizeof(char));
    expectedList.channels[2].channelName = (char *)malloc((strlen(TEST_CHANNEL2_NAME) + 1) * sizeof(char));
    strcpy(expectedList.channels[2].channelID, TEST_CHANNEL2_ID);
    strcpy(expectedList.channels[2].channelName, TEST_CHANNEL2_NAME);

    expectedList.channels[3].channelID = (char *)malloc((strlen(TEST_CHANNEL3_ID) + 1) * sizeof(char));
    expectedList.channels[3].channelName = (char *)malloc((strlen(TEST_CHANNEL3_NAME) + 1) * sizeof(char));
    strcpy(expectedList.channels[3].channelID, TEST_CHANNEL3_ID);
    strcpy(expectedList.channels[3].channelName, TEST_CHANNEL3_NAME);

    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    outputListText = fopen(".\\mocksvr\\ouconlis.txt", "rb");

    while((read = fgetc(outputListText)) != EOF){
        lpGlobalMemory[dindex] = read;
        dindex++;
    }

    fclose(outputListText);

    jsnparse_parseChannelList(lpGlobalMemory, dindex, &actualList);

    if(expectedList.numChannels == actualList.numChannels){

        for(index = 0; index < expectedList.numChannels; index++){
            if (strcmp (expectedList.channels[index].channelID, actualList.channels[index].channelID) != 0){
                printf("fail %s\n", expectedList.channels[index].channelID);
                testResult = FALSE;
                break;
            }

            if (strcmp (expectedList.channels[index].channelName, actualList.channels[index].channelName) != 0){
                printf("fail %s\n", expectedList.channels[index].channelName);
                testResult = FALSE;
                break;
            }

        }

    } else {
        testResult = FALSE;
        printf("Not enough channels expected %d, got %d\n", expectedList.numChannels, actualList.numChannels);
    }



    jsnparse_freeChannelList(&expectedList);

    GlobalFreePtr(lpGlobalMemory);

    return testResult;
}

BOOL test_jsnparse(){

    BOOL result = TRUE;
    BOOL intermediateResult;

    intermediateResult = test_jsnparse_parseChannelList();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseChannelList() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseChannelList() failed\n");
    }

    intermediateResult = test_jsnparse_parseMessageList();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseMessageList() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseMessageList() failed\n");
    }

    return result;
}
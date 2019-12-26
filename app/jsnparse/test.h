#include "jsnparse.h"
#include "windows.h"
#include "..\tstconst.h"
#include <stdlib.h>

LPSTR lpGlobalMemory;
DWORD allocatedMemorySize;

BOOL test_jsnparse_parseMessageList1(){
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

    jsnparse_freeMessagesList(&actualList);
    jsnparse_freeMessagesList(&expectedList);

    return testResult;

}

BOOL test_jsnparse_parseMessageList2(){
    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    MessageList expectedList = {NULL, 7};
    MessageList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    //There are 50 messages in the text file but due to json parsing limitations, we can only see the latest 7.
    expectedList.messages = (Message *) malloc(7 * sizeof(Message));

    expectedList.messages[0].message = (char *)malloc((strlen("hi from win 3.1") + 1) * sizeof(char));
    strcpy(expectedList.messages[0].message, "hi from win 3.1");

    expectedList.messages[1].message = (char *)malloc((strlen("hi win 3.1 from mac") + 1) * sizeof(char));
    strcpy(expectedList.messages[1].message, "hi win 3.1 from mac");

    expectedList.messages[2].message = (char *)malloc((strlen("hi mac from win 3.1") + 1) * sizeof(char));
    strcpy(expectedList.messages[2].message, "hi mac from win 3.1");

    expectedList.messages[3].message = (char *)malloc((strlen("hi world! This is win 3.1") + 1) * sizeof(char));
    strcpy(expectedList.messages[3].message, "hi world! This is win 3.1");   

    expectedList.messages[4].message = (char *)malloc((strlen("eu") + 1) * sizeof(char));
    strcpy(expectedList.messages[4].message, "eu");

    expectedList.messages[5].message = (char *)malloc((strlen("Hieveryone") + 1) * sizeof(char));
    strcpy(expectedList.messages[5].message, "Hieveryone");

    expectedList.messages[6].message = (char *)malloc((strlen("Hi to <#CPV9L2UJV|random>  channel!") + 1) * sizeof(char));
    strcpy(expectedList.messages[6].message, "Hi to <#CPV9L2UJV|random>  channel!");


    for(index = 0; index < 7; index++){
        expectedList.messages[index].userID = (char *)malloc((strlen("UQ2NT009J") + 1) * sizeof(char));
        strcpy(expectedList.messages[index].userID, "UQ2NT009J");
    }

    outputListText = fopen(".\\mocksvr\\ouconhi2.txt", "rb");

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

    jsnparse_freeMessagesList(&actualList);
    jsnparse_freeMessagesList(&expectedList);

    return testResult;

}

BOOL test_jsnparse_parseChannelList(){

    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    ChannelList expectedList = {NULL, 4};
    ChannelList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    expectedList.channels = (Channel *) malloc(4 * sizeof(Channel));

    expectedList.channels[0].channelID = (char *)malloc((strlen("CPV9L2UJV") + 1) * sizeof(char));
    expectedList.channels[0].channelName = (char *)malloc((strlen("random") + 1) * sizeof(char));
    strcpy(expectedList.channels[0].channelID, "CPV9L2UJV");
    strcpy(expectedList.channels[0].channelName, "random");

    expectedList.channels[1].channelID = (char *)malloc((strlen("CPV9L2VT3") + 1) * sizeof(char));
    expectedList.channels[1].channelName = (char *)malloc((strlen("win31") + 1) * sizeof(char));
    strcpy(expectedList.channels[1].channelID, "CPV9L2VT3");
    strcpy(expectedList.channels[1].channelName,"win31");

    expectedList.channels[2].channelID = (char *)malloc((strlen("CQ2NUCLDA") + 1) * sizeof(char));
    expectedList.channels[2].channelName = (char *)malloc((strlen("playground") + 1) * sizeof(char));
    strcpy(expectedList.channels[2].channelID, "CQ2NUCLDA");
    strcpy(expectedList.channels[2].channelName, "playground");

    expectedList.channels[3].channelID = (char *)malloc((strlen("CQ52U515M") + 1) * sizeof(char));
    expectedList.channels[3].channelName = (char *)malloc((strlen("general") + 1) * sizeof(char));
    strcpy(expectedList.channels[3].channelID, "CQ52U515M");
    strcpy(expectedList.channels[3].channelName, "general");

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


    jsnparse_freeChannelList(&actualList);
    jsnparse_freeChannelList(&expectedList);

    return testResult;
}

BOOL test_jsnparse_parseUserList(){

    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    UserList expectedList = {NULL, 2};
    UserList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    expectedList.users = (User *) malloc(2 * sizeof(User));

    expectedList.users[0].userID = (char *)malloc((strlen("USLACKBOT") + 1) * sizeof(char));
    expectedList.users[0].username = (char *)malloc((strlen("slackbot") + 1) * sizeof(char));
    strcpy(expectedList.users[0].userID, "USLACKBOT");
    strcpy(expectedList.users[0].username, "slackbot");

    expectedList.users[1].userID = (char *)malloc((strlen("UQ2NT009J") + 1) * sizeof(char));
    expectedList.users[1].username = (char *)malloc((strlen("yeokm1") + 1) * sizeof(char));
    strcpy(expectedList.users[1].userID, "UQ2NT009J");
    strcpy(expectedList.users[1].username, "yeokm1");

    outputListText = fopen(".\\mocksvr\\ouusrlis.txt", "rb");

    while((read = fgetc(outputListText)) != EOF){
        lpGlobalMemory[dindex] = read;
        dindex++;
    }

    fclose(outputListText);

    jsnparse_parseUserList(lpGlobalMemory, dindex, &actualList);

    if(expectedList.numUsers == actualList.numUsers){

        for(index = 0; index < expectedList.numUsers; index++){
            if (strcmp (expectedList.users[index].userID, actualList.users[index].userID) != 0){
                printf("fail %s\n", expectedList.users[index].userID);
                testResult = FALSE;
                break;
            }

            if (strcmp (expectedList.users[index].username, actualList.users[index].username) != 0){
                printf("fail %s\n", expectedList.users[index].username);
                testResult = FALSE;
                break;
            }

        }

    } else {
        testResult = FALSE;
        printf("Not enough users expected %d, got %d\n", expectedList.numUsers, actualList.numUsers);
    }


    jsnparse_freeUserList(&actualList);
    jsnparse_freeUserList(&expectedList);

    return testResult;
}

BOOL test_jsnparse(){

    BOOL result = TRUE;
    BOOL intermediateResult;
    int i = 0;

    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    intermediateResult = test_jsnparse_parseChannelList();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseChannelList() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseChannelList() failed\n");
    }

    intermediateResult = test_jsnparse_parseMessageList1();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseMessageList1() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseMessageList1() failed\n");
    }

    intermediateResult = test_jsnparse_parseMessageList2();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseMessageList2() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseMessageList2() failed\n");
    }

    intermediateResult = test_jsnparse_parseUserList();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseUserList() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseUserList() failed\n");
    }

    return result;
}
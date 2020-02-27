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
    MessageList expectedList = {NULL, 10};
    MessageList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    expectedList.messages = (Message *) malloc(10 * sizeof(Message));

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

    expectedList.messages[7].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[7].message, "hello");

    expectedList.messages[8].message = (char *)malloc((strlen("hello") + 1) * sizeof(char));
    strcpy(expectedList.messages[8].message, "hello");

    expectedList.messages[9].message = (char *)malloc((strlen("hello retro test!") + 1) * sizeof(char));
    strcpy(expectedList.messages[9].message, "hello retro test!");

    for(index = 0; index < 10; index++){
        expectedList.messages[index].userID = (char *)malloc((strlen("UQ2NT009J") + 1) * sizeof(char));
        strcpy(expectedList.messages[index].userID, "UQ2NT009J");
    }

    outputListText = fopen(".\\mocksvr\\ouconhis.txt", "rb");

    while((read = fgetc(outputListText)) != EOF){
        lpGlobalMemory[dindex] = read;
        dindex++;
    }

    fclose(outputListText);

    jsnparse_parseMessageList(lpGlobalMemory, dindex, &actualList, TEST_MAX_MESSAGES);

    if(expectedList.numMessages == actualList.numMessages){

        for(index = 0; index < expectedList.numMessages; index++){
            if (strcmp (expectedList.messages[index].userID, actualList.messages[index].userID) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.messages[index].userID, expectedList.messages[index].userID);
                testResult = FALSE;
            }

            if (strcmp (expectedList.messages[index].message, actualList.messages[index].message) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.messages[index].message, expectedList.messages[index].message);
                testResult = FALSE;
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

    expectedList.messages = (Message *) malloc(15 * sizeof(Message));

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

    jsnparse_parseMessageList(lpGlobalMemory, dindex, &actualList, TEST_MAX_MESSAGES);

    if(expectedList.numMessages == actualList.numMessages){

        for(index = 0; index < expectedList.numMessages; index++){
            if (strcmp (expectedList.messages[index].userID, actualList.messages[index].userID) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.messages[index].userID, expectedList.messages[index].userID);
                testResult = FALSE;
            }

            if (strcmp (expectedList.messages[index].message, actualList.messages[index].message) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.messages[index].message, expectedList.messages[index].message);
                testResult = FALSE;
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
                printf("%d: Got <%s> expected <%s>\n", index, actualList.channels[index].channelID, expectedList.channels[index].channelID);
                testResult = FALSE;
            }

            if (strcmp (expectedList.channels[index].channelName, actualList.channels[index].channelName) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.channels[index].channelID, expectedList.channels[index].channelName);
                testResult = FALSE;
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
                printf("%d: Got <%s> expected <%s>\n", index, actualList.users[index].userID,  expectedList.users[index].userID);
                testResult = FALSE;
            }

            if (strcmp (expectedList.users[index].username, actualList.users[index].username) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.users[index].username, expectedList.users[index].username);
                testResult = FALSE;
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

BOOL test_jsnparse_parseUserList2(){

    DWORD dindex = 0;
    int index = 0;
    FILE *outputListText;
    char read;
    UserList expectedList = {NULL, 24};
    UserList actualList = {NULL, 0};
    BOOL testResult = TRUE;

    expectedList.users = (User *) malloc(24 * sizeof(User));

    expectedList.users[0].userID = (char *)malloc((strlen("USLACKBOT") + 1) * sizeof(char));
    expectedList.users[0].username = (char *)malloc((strlen("slackbot") + 1) * sizeof(char));
    strcpy(expectedList.users[0].userID, "USLACKBOT");
    strcpy(expectedList.users[0].username, "slackbot");

    expectedList.users[1].userID = (char *)malloc((strlen("UCPDZ69LK") + 1) * sizeof(char));
    expectedList.users[1].username = (char *)malloc((strlen("eric") + 1) * sizeof(char));
    strcpy(expectedList.users[1].userID, "UCPDZ69LK");
    strcpy(expectedList.users[1].username, "eric");

    expectedList.users[2].userID = (char *)malloc((strlen("UCS75QB27") + 1) * sizeof(char));
    expectedList.users[2].username = (char *)malloc((strlen("lori.emerson") + 1) * sizeof(char));
    strcpy(expectedList.users[2].userID, "UCS75QB27");
    strcpy(expectedList.users[2].username, "lori.emerson");

    expectedList.users[3].userID = (char *)malloc((strlen("UCT663ZDG") + 1) * sizeof(char));
    expectedList.users[3].username = (char *)malloc((strlen("will") + 1) * sizeof(char));
    strcpy(expectedList.users[3].userID, "UCT663ZDG");
    strcpy(expectedList.users[3].username, "will");

    expectedList.users[4].userID = (char *)malloc((strlen("UCTLQS7B8") + 1) * sizeof(char));
    expectedList.users[4].username = (char *)malloc((strlen("seth") + 1) * sizeof(char));
    strcpy(expectedList.users[4].userID, "UCTLQS7B8");
    strcpy(expectedList.users[4].username, "seth");

    expectedList.users[5].userID = (char *)malloc((strlen("UGLGZ36QY") + 1) * sizeof(char));
    expectedList.users[5].username = (char *)malloc((strlen("securabbit") + 1) * sizeof(char));
    strcpy(expectedList.users[5].userID, "UGLGZ36QY");
    strcpy(expectedList.users[5].username, "securabbit");

    expectedList.users[6].userID = (char *)malloc((strlen("UGM6G23GU") + 1) * sizeof(char));
    expectedList.users[6].username = (char *)malloc((strlen("cebrock106") + 1) * sizeof(char));
    strcpy(expectedList.users[6].userID, "UGM6G23GU");
    strcpy(expectedList.users[6].username, "cebrock106");

    expectedList.users[7].userID = (char *)malloc((strlen("UGM7MKYVA") + 1) * sizeof(char));
    expectedList.users[7].username = (char *)malloc((strlen("maya.livio") + 1) * sizeof(char));
    strcpy(expectedList.users[7].userID, "UGM7MKYVA");
    strcpy(expectedList.users[7].username, "maya.livio");

    expectedList.users[8].userID = (char *)malloc((strlen("UGNPGE8R0") + 1) * sizeof(char));
    expectedList.users[8].username = (char *)malloc((strlen("chris.torrence") + 1) * sizeof(char));
    strcpy(expectedList.users[8].userID, "UGNPGE8R0");
    strcpy(expectedList.users[8].username, "chris.torrence");

    expectedList.users[9].userID = (char *)malloc((strlen("UGQALP7GD") + 1) * sizeof(char));
    expectedList.users[9].username = (char *)malloc((strlen("striegl") + 1) * sizeof(char));
    strcpy(expectedList.users[9].userID, "UGQALP7GD");
    strcpy(expectedList.users[9].username, "striegl");

    expectedList.users[10].userID = (char *)malloc((strlen("UGTT3MN5R") + 1) * sizeof(char));
    expectedList.users[10].username = (char *)malloc((strlen("alexandra.wilson") + 1) * sizeof(char));
    strcpy(expectedList.users[10].userID, "UGTT3MN5R");
    strcpy(expectedList.users[10].username, "alexandra.wilson");

    expectedList.users[11].userID = (char *)malloc((strlen("UGVNV48AH") + 1) * sizeof(char));
    expectedList.users[11].username = (char *)malloc((strlen("williegoat") + 1) * sizeof(char));
    strcpy(expectedList.users[11].userID, "UGVNV48AH");
    strcpy(expectedList.users[11].username, "williegoat");

    expectedList.users[12].userID = (char *)malloc((strlen("UH46D0BEH") + 1) * sizeof(char));
    expectedList.users[12].username = (char *)malloc((strlen("theelk801") + 1) * sizeof(char));
    strcpy(expectedList.users[12].userID, "UH46D0BEH");
    strcpy(expectedList.users[12].username, "theelk801");

    expectedList.users[13].userID = (char *)malloc((strlen("UH565HA04") + 1) * sizeof(char));
    expectedList.users[13].username = (char *)malloc((strlen("alwi1816") + 1) * sizeof(char));
    strcpy(expectedList.users[13].userID, "UH565HA04");
    strcpy(expectedList.users[13].username, "alwi1816");

    expectedList.users[14].userID = (char *)malloc((strlen("UHSL3KYKS") + 1) * sizeof(char));
    expectedList.users[14].username = (char *)malloc((strlen("lauraonsale") + 1) * sizeof(char));
    strcpy(expectedList.users[14].userID, "UHSL3KYKS");
    strcpy(expectedList.users[14].username, "lauraonsale");

    expectedList.users[15].userID = (char *)malloc((strlen("UJE8JUR41") + 1) * sizeof(char));
    expectedList.users[15].username = (char *)malloc((strlen("shanel.wu") + 1) * sizeof(char));
    strcpy(expectedList.users[15].userID, "UJE8JUR41");
    strcpy(expectedList.users[15].username, "shanel.wu");

    expectedList.users[16].userID = (char *)malloc((strlen("UKADKRXA5") + 1) * sizeof(char));
    expectedList.users[16].username = (char *)malloc((strlen("kwbeam") + 1) * sizeof(char));
    strcpy(expectedList.users[16].userID, "UKADKRXA5");
    strcpy(expectedList.users[16].username, "kwbeam");

    expectedList.users[17].userID = (char *)malloc((strlen("UMPK3H6F5") + 1) * sizeof(char));
    expectedList.users[17].username = (char *)malloc((strlen("deke4297") + 1) * sizeof(char));
    strcpy(expectedList.users[17].userID, "UMPK3H6F5");
    strcpy(expectedList.users[17].username, "deke4297");

    expectedList.users[18].userID = (char *)malloc((strlen("UN39C3A8N") + 1) * sizeof(char));
    expectedList.users[18].username = (char *)malloc((strlen("malinda.dietrich") + 1) * sizeof(char));
    strcpy(expectedList.users[18].userID, "UN39C3A8N");
    strcpy(expectedList.users[18].username, "malinda.dietrich");

    expectedList.users[19].userID = (char *)malloc((strlen("UP5SSLVQA") + 1) * sizeof(char));
    expectedList.users[19].username = (char *)malloc((strlen("autumn.tyler") + 1) * sizeof(char));
    strcpy(expectedList.users[19].userID, "UP5SSLVQA");
    strcpy(expectedList.users[19].username, "autumn.tyler");

    expectedList.users[20].userID = (char *)malloc((strlen("UPC7H5X09") + 1) * sizeof(char));
    expectedList.users[20].username = (char *)malloc((strlen("amandahurtado") + 1) * sizeof(char));
    strcpy(expectedList.users[20].userID, "UPC7H5X09");
    strcpy(expectedList.users[20].username, "amandahurtado");

    expectedList.users[21].userID = (char *)malloc((strlen("USLRMQH4Y") + 1) * sizeof(char));
    expectedList.users[21].username = (char *)malloc((strlen("doodle_bot") + 1) * sizeof(char));
    strcpy(expectedList.users[21].userID, "USLRMQH4Y");
    strcpy(expectedList.users[21].username, "doodle_bot");

    expectedList.users[22].userID = (char *)malloc((strlen("USXRBJDU3") + 1) * sizeof(char));
    expectedList.users[22].username = (char *)malloc((strlen("michael.connor") + 1) * sizeof(char));
    strcpy(expectedList.users[22].userID, "USXRBJDU3");
    strcpy(expectedList.users[22].username, "michael.connor");

    expectedList.users[23].userID = (char *)malloc((strlen("UTVU962TA") + 1) * sizeof(char));
    expectedList.users[23].username = (char *)malloc((strlen("w31slack") + 1) * sizeof(char));
    strcpy(expectedList.users[23].userID, "UTVU962TA");
    strcpy(expectedList.users[23].username, "w31slack");

    outputListText = fopen(".\\mocksvr\\ouusrli2.txt", "rb");

    while((read = fgetc(outputListText)) != EOF){
        lpGlobalMemory[dindex] = read;
        dindex++;
    }

    fclose(outputListText);

    jsnparse_parseUserList(lpGlobalMemory, dindex, &actualList);

    if(expectedList.numUsers == actualList.numUsers){

        for(index = 0; index < expectedList.numUsers; index++){
            if (strcmp (expectedList.users[index].userID, actualList.users[index].userID) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.users[index].userID,  expectedList.users[index].userID);
                testResult = FALSE;
            }

            if (strcmp (expectedList.users[index].username, actualList.users[index].username) != 0){
                printf("%d: Got <%s> expected <%s>\n", index, actualList.users[index].username, expectedList.users[index].username);
                testResult = FALSE;
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

    intermediateResult = test_jsnparse_parseUserList2();

    if(intermediateResult){
        OutputDebugString("test_jsnparse_parseUserList2() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_jsnparse_parseUserList2() failed\n");
    }

    return result;
}
#include "restapi.h"
#include "windows.h"
#include "..\tstconst.h"
#include "stdio.h"


static BOOL test_restapi_sendMessageToChannel(){

    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;
    char read[1];
    FILE *outputPostMessage;
    DWORD index = 0;
    DWORD bytesReceived;

    BOOL testResult = TRUE;

    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    bytesReceived = restapi_sendMessageToChannel(TEST_MOCK_SERVER_IP, TEST_MOCK_PROXY_SERVER_PORT, TEST_CHANNEL_ID, TEST_MESSAGE, TEST_TOKEN, lpGlobalMemory, allocatedMemorySize);

    outputPostMessage = fopen(".\\mocksvr\\ouposmsg.txt", "rb");

    if(outputPostMessage == NULL){
      printf("Cannot open result file\n");
      testResult = FALSE;
   } else {

        while((read[0] = fgetc(outputPostMessage)) != EOF){
            if(lpGlobalMemory[index] != read[0]){
                testResult = FALSE;
                break;
            }
            index++;
        }

        fclose(outputPostMessage);
   }

    GlobalFreePtr(lpGlobalMemory);

    return testResult;
}

static BOOL test_restapi_getChannelMessages(){

    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;
    char read[1];
    FILE *outputGetMessage;
    DWORD index = 0;
    DWORD bytesReceived;

    BOOL testResult = TRUE;

    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    bytesReceived = restapi_getChannelMessages(TEST_MOCK_SERVER_IP, TEST_MOCK_PROXY_SERVER_PORT, TEST_CHANNEL_ID, TEST_TOKEN, lpGlobalMemory, allocatedMemorySize);

    outputGetMessage = fopen(".\\mocksvr\\ouconhis.txt", "rb");

    if(outputGetMessage == NULL){
      printf("Cannot open result file\n");
      testResult = FALSE;
   } else {

        while((read[0] = fgetc(outputGetMessage)) != EOF){
            if(lpGlobalMemory[index] != read[0]){
                testResult = FALSE;
                break;
            }
            index++;
        }

        fclose(outputGetMessage);
   }

    GlobalFreePtr(lpGlobalMemory);

    return testResult;
}

static BOOL test_restapi_getChannelList(){

    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;
    char read[1];
    FILE *outputGetMessage;
    DWORD index = 0;
    DWORD bytesReceived;

    BOOL testResult = TRUE;

    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    bytesReceived = restapi_getChannelList(TEST_MOCK_SERVER_IP, TEST_MOCK_PROXY_SERVER_PORT, TEST_TOKEN, lpGlobalMemory, allocatedMemorySize);

    outputGetMessage = fopen(".\\mocksvr\\ouconlis.txt", "rb");

    if(outputGetMessage == NULL){
      printf("Cannot open result file\n");
      testResult = FALSE;
   } else {

        while((read[0] = fgetc(outputGetMessage)) != EOF){
            if(lpGlobalMemory[index] != read[0]){
                testResult = FALSE;
                break;
            }
            index++;
        }

        fclose(outputGetMessage);
   }

    GlobalFreePtr(lpGlobalMemory);

    return testResult;
}

BOOL test_restapi(){

    BOOL result = TRUE;
    BOOL intermediateResult;

    intermediateResult = test_restapi_sendMessageToChannel();

    if(intermediateResult){
        OutputDebugString("test_restapi_sendMessageToChannel() passed\n"); 
     } else {
        result = FALSE;
        OutputDebugString("test_restapi_sendMessageToChannel() failed\n");
    }


    intermediateResult = test_restapi_getChannelMessages();

    if(intermediateResult){
         OutputDebugString("test_restapi_getChannelMessages() passed\n"); 
    } else {
        result = FALSE;
        OutputDebugString("test_restapi_getChannelMessages() failed\n");
    }


    intermediateResult = test_restapi_getChannelList();

    if(intermediateResult){
         OutputDebugString("test_restapi_getChannelList() passed\n"); 
    } else {
        result = FALSE;
        OutputDebugString(" test_restapi_getChannelList() failed\n");
    }


    return result;
}

#include "network\network.h"
#include "windowsx.h"
#include "string.h"
#include "..\tstconst.h"

#define TEXT_TO_SEND "Dummy test send 123456789"
#define MAX_SMALL_RESPONSE_LENGTH 100

char response[MAX_SMALL_RESPONSE_LENGTH];

static BOOL test_data_send_recv(){

    int outgoingSocketID;
    BOOL testStatus = TRUE;
    int bytesReceived;

    outgoingSocketID = network_createTCPSocket();

    if(outgoingSocketID < 0){
        OutputDebugString("Cannot create outgoing TCP socket\n");
        testStatus = FALSE;
    }

    if(network_connectToSocket(outgoingSocketID, TEST_MOCK_SERVER_IP, TEST_MOCK_REPLAY_SERVER_PORT) < 0){
        OutputDebugString("Cannot connect to socket\n");
        testStatus = FALSE;   
    }


    if(network_sendData(outgoingSocketID, TEXT_TO_SEND, strlen(TEXT_TO_SEND)) == (int) strlen(TEXT_TO_SEND)){
  
      bytesReceived = network_recvData(outgoingSocketID, response, MAX_SMALL_RESPONSE_LENGTH);
     
      if(!(((int) strlen(TEXT_TO_SEND) == bytesReceived) 
        && (strcmp(TEXT_TO_SEND, response) == 0))){
        
        OutputDebugString("Did not receive required correct string\n");
        testStatus = FALSE; 
      }

    } else {
        OutputDebugString("Did not sent required bytes\n");
        testStatus = FALSE;  
    }

    network_closeSocket(outgoingSocketID);

    return testStatus;
}

static BOOL test_large_data_send_recv(){

    int outgoingSocketID;
    BOOL testStatus = TRUE;
    DWORD bytesReceived;
    LPSTR lpGlobalMemory;
    DWORD allocatedMemorySize;

    outgoingSocketID = network_createTCPSocket();

    if(outgoingSocketID < 0){
        OutputDebugString("Cannot create outgoing TCP socket\n");
        testStatus = FALSE;
    }

    if(network_connectToSocket(outgoingSocketID, TEST_MOCK_SERVER_IP, TEST_MOCK_REPLAY_SERVER_PORT) < 0){
        OutputDebugString("Cannot connect to socket\n");
        testStatus = FALSE;   
    }


    lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, TEST_MAX_GLOBAL_MEMORY_ALLOCATION);
    allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

    if(network_sendData(outgoingSocketID, TEXT_TO_SEND, strlen(TEXT_TO_SEND)) == (int) strlen(TEXT_TO_SEND)){
  
      bytesReceived = network_recvLargeData(outgoingSocketID, lpGlobalMemory, allocatedMemorySize);
     
      if(!(((DWORD) strlen(TEXT_TO_SEND) == bytesReceived) 
        && (strcmp(TEXT_TO_SEND, response) == 0))){
        
        OutputDebugString("Did not receive required correct string\n");
        testStatus = FALSE; 
      }

    } else {
        OutputDebugString("Did not sent required bytes\n");
        testStatus = FALSE;  
    }

    GlobalFreePtr(lpGlobalMemory);

    network_closeSocket(outgoingSocketID);

    return testStatus;
}

BOOL test_network(){

    BOOL result = TRUE;
    BOOL intermediateResult;

    intermediateResult = test_data_send_recv();

    if(intermediateResult){
        OutputDebugString("test_data_send_recv() passed\n");
    } else{
        result = FALSE;
        OutputDebugString("test_data_send_recv() failed\n");
    }

    intermediateResult = test_large_data_send_recv();

    if(intermediateResult){
        OutputDebugString("test_large_data_send_recv() passed\n");
    } else {
        result = FALSE;
        OutputDebugString("test_large_data_send_recv failed\n");
    }

    return result;
}
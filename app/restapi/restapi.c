#include "restapi.h"
#include "../network/network.h"
#include "string.h"
#include <stdio.h> 

#define MAX_REQUEST_SIZE 500
#define POST_MESSAGE_FORMAT "POST /api/chat.postMessage?channel=%s&as_user=true&text=%s HTTP/1.1\r\nHost: slack.com\r\nAuthorization: Bearer %s\r\nAccept: */*\r\nConnection: close\r\n\r\n"
#define GET_MESSAGES_FORMAT "GET /api/conversations.history?channel=%s&limit=%d HTTP/1.1\r\nHost: slack.com\r\nAuthorization: Bearer %s\r\nAccept: */*\r\nConnection: close\r\n\r\n"
#define GET_CHANNEL_LIST "GET /api/conversations.list HTTP/1.1\r\nHost: slack.com\r\nAuthorization: Bearer %s\r\nAccept: */*\r\nConnection: close\r\n\r\n"
#define GET_USERS_LIST "GET /api/users.list HTTP/1.1\r\nHost: slack.com\r\nAuthorization: Bearer %s\r\nAccept: */*\r\nConnection: close\r\n\r\n"

static DWORD restapi_sendRequest(char * ip, int port, char * request, int requestLength, LPSTR response, DWORD maxResponseLength){

    int socketID;
    DWORD bytesReceived = 0;

    socketID = network_createTCPSocket();

    if(socketID >= 0){

        if(network_connectToSocket(socketID, ip, port) >= 0){
            if(network_sendData(socketID, request, requestLength) >= 0){
                bytesReceived = network_recvLargeData(socketID, response, maxResponseLength);
            } else {
                printf("Cannot send data\n");
            }

        } else {
            printf("Cannot connect to socket\n");
        }

    } else {
       printf("Cannot create outgoing TCP socket\n");
    }

    network_closeSocket(socketID);

    return bytesReceived;
}

DWORD restapi_sendMessageToChannel(char * ip, int port, char * channel, char * message, char * token, LPSTR response, DWORD maxResponseLength){
    int requestLength;
    DWORD bytesReceived = 0;
    char buff[MAX_REQUEST_SIZE];

    requestLength = sprintf(buff, POST_MESSAGE_FORMAT, channel, message, token);

    bytesReceived = restapi_sendRequest(ip, port, buff, requestLength, response, maxResponseLength);

    return bytesReceived;
}

DWORD restapi_getChannelMessages(char * ip, int port, char * channel, int limit, char * token, LPSTR response, DWORD maxResponseLength){
    int requestLength;
    DWORD bytesReceived = 0;
    char buff[MAX_REQUEST_SIZE];
    
    requestLength = sprintf(buff, GET_MESSAGES_FORMAT, channel, limit, token);

    bytesReceived = restapi_sendRequest(ip, port, buff, requestLength, response, maxResponseLength);

    return bytesReceived;
}

DWORD restapi_getChannelList(char * ip, int port, char * token, LPSTR response, DWORD maxResponseLength){
    int requestLength;
    DWORD bytesReceived = 0;
    char buff[MAX_REQUEST_SIZE];
    
    requestLength = sprintf(buff, GET_CHANNEL_LIST, token);

    bytesReceived = restapi_sendRequest(ip, port, buff, requestLength, response, maxResponseLength);

    return bytesReceived;
}

DWORD restapi_getUsersList(char * ip, int port, char * token, LPSTR response, DWORD maxResponseLength){
    int requestLength;
    DWORD bytesReceived = 0;
    char buff[MAX_REQUEST_SIZE];
    
    requestLength = sprintf(buff, GET_USERS_LIST, token);

    bytesReceived = restapi_sendRequest(ip, port, buff, requestLength, response, maxResponseLength);

    return bytesReceived;
}
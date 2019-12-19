#include "network.h"
#include <winsock.h>
#include <stddef.h>
#include "..\smprintf.h"


#pragma comment(lib,"winsock.lib")

//VC 1.52 does not have the following
#define MAKEWORD(low, high) ((WORD)((((WORD)(high)) << 8) | ((BYTE)(low))))

static int winsockStartupOk = 0;

// We have problems importing string so implementing memset here
//https://clc-wiki.net/wiki/memset
static void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}


static int network_initWinsockInstance(){

    WSADATA wsaData;
    int nErrorStatus;
    WORD wVersionRequested = MAKEWORD(1, 1);

    //printf("Starting Winsock instance\n");

    nErrorStatus = WSAStartup(wVersionRequested, &wsaData);

    if (nErrorStatus != 0) {
        printf("WSAStartup failed with error %ld\n", WSAGetLastError());
        return -1;
    }
    // check the WinSock version information
    if ( (LOBYTE(wsaData.wVersion) != LOBYTE(wVersionRequested)) ||
    (HIBYTE(wsaData.wVersion) != HIBYTE(wVersionRequested)) ) {

        printf("System's winsock.dll %u.%u version is not supported by application\n", LOBYTE(wsaData.wVersion),HIBYTE(wsaData.wVersion));
        network_exitWinsockInstance();
        return -2;
    }

    winsockStartupOk = 1;

    // printf("Winsock description: %s\n", wsaData.szDescription);
    // printf("Winsock system status: %s\n", wsaData.szSystemStatus);
    // printf("Winsock max sockets %d\n", wsaData.iMaxSockets);
    // printf("Winsock max UDP size %d\n", wsaData.iMaxUdpDg);

    return 0;
}

static void network_exitWinsockInstance(){

    //printf("Exit Winsock instance\n");
    if(winsockStartupOk){
        WSACleanup(); // terminate WinSock use
    }

    winsockStartupOk = 0;
}

int network_createTCPSocket(){
    int sock;

    if(!winsockStartupOk){
        network_initWinsockInstance();
    }

    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    return sock;
}

int network_connectToSocket(int socketID, char * ipaddress, int port){

    int error = 0;

    struct sockaddr_in serveraddr;

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family      = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(ipaddress);
    serveraddr.sin_port        = htons((unsigned short) port);

    error = connect(socketID, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

    return error;
}

int network_closeSocket(int socketID){
    return closesocket(socketID);
}


int network_sendData(int socketID, char * request, int requestLength){

    int bytesSent;

    bytesSent = send(socketID, request, requestLength, 0);

    return bytesSent;
}

int network_recvData(int socketID, char * response, int maxResponseLength){

    char buff[1];
    int bytesReceivedThisInstant = 0;
    int totalBytesSaved = 0;

    do {
        bytesReceivedThisInstant = recv(socketID, (char *) &buff, 1, 0);

        if(bytesReceivedThisInstant <= 0){
            return totalBytesSaved;
        }

        response[totalBytesSaved] = buff[0];
        totalBytesSaved++;

    } while(bytesReceivedThisInstant > 0 && (totalBytesSaved <= maxResponseLength));

    return totalBytesSaved;
}

DWORD network_recvLargeData(int socketID, LPSTR response, DWORD maxResponseLength){
    char buff[1];
    int bytesReceivedThisInstant = 0;
    DWORD totalBytesSaved = 0;

    do {
        bytesReceivedThisInstant = recv(socketID, (char *) &buff, 1, 0);

        if(bytesReceivedThisInstant <= 0){
            return totalBytesSaved;
        }

        response[totalBytesSaved] = buff[0];
        totalBytesSaved++;

    } while(bytesReceivedThisInstant > 0 && (totalBytesSaved <= maxResponseLength));

    return totalBytesSaved;
}
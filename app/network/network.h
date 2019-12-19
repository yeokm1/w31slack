#ifndef NETWORK_H
#define NETWORK_H

#include <windows.h>


static int network_initWinsockInstance();

static void network_exitWinsockInstance();

//Returs socket ID if successful. Returns negative value if unsuccessful
int network_createTCPSocket();

int network_connectToSocket(int socketID, char * ipaddress, int port);

//Returns 0 if successfull.
int network_closeSocket(int socketID);

int network_sendData(int socketID, char * request, int requestLength);
int network_recvData(int socketID, char * response, int maxResponseLength);
DWORD network_recvLargeData(int socketID, LPSTR response, DWORD maxResponseLength);

#endif


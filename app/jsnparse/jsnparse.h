#ifndef JSNPARSE_H
#define JSNPARSE_H
#include "windows.h"

typedef struct 
{
    char * channelName;
    char * channelID;
} Channel;

typedef struct 
{
    Channel * channels;
    int numChannels;
} ChannelList;

typedef struct 
{
    char * message;
    char * userID;
} Message;

typedef struct 
{
    Message * messages;
    int numMessages;
} MessageList;


void jsnparse_parseChannelList(LPSTR response, DWORD length, ChannelList * list);
void jsnparse_parseMessageList(LPSTR response, DWORD length, MessageList * list);


void jsnparse_freeChannelList(ChannelList * list);
void jsnparse_freeMessagesList(MessageList * list);

#endif

#include "AboutDlg.h"
#include "Globals.h"
#include "MainWnd.h"
#include "Resource.h"
#include <stdio.h> 
#include <stdlib.h>
#include <windowsx.h>
#include <string.h>
#include <time.h>

#include "restapi/restapi.h"
#include "jsnparse/jsnparse.h"
#include "escapes.h"


#define CONFIG_FILE_TO_OPEN "w31slack.ini"
#define TOKEN_LENGTH_MAX 90
#define IP_MAX 20

#define MAX_MESSAGES_TO_PARSE 10

#define MAX_GLOBAL_MEM_ALLOCATION 32000

#define SINGLE_SHOT_TIMER_ID 4
#define REFRESH_TIMER_ID 6
#define CHANNELS_BOX_ID 5
#define LIST_BOX_ID 6
#define TEXT_FIELD_ID 8
#define STATUS_BAR_ID 9

#define MAX_MESSAGE_FROM_BOX 50
#define MAX_MESSAGE_TO_SEND MAX_MESSAGE_FROM_BOX * 3

/* Main window class and title */
static const char MainWndClass[] = "Slack for Win 3.1";

HWND hwnd;
HWND textField;
HWND sendButton;
HWND channelMessageBox;
HWND channelsBox;

RECT statusRect;

char token[TOKEN_LENGTH_MAX];
int refreshRate = 1000;
char ip[IP_MAX];
int port;
char statusText[MAX_MESSAGE_TO_SEND + 20];

BOOL usersObtained = FALSE;
BOOL channelsObtained = FALSE;

ChannelList channelsList = {NULL, 0};
MessageList messagesList = {NULL, 0};
UserList usersList = {NULL, 0};

int currentSelectedChannel = 0;

LPSTR lpGlobalMemory;
DWORD allocatedMemorySize;

HBRUSH hbrush;

BOOL openAndProcessConfigFile(char * filename){
  FILE * configFile;
  char buff[6];

  configFile = fopen(filename, "r");
  if(configFile == NULL){
    return FALSE;
  }


  fgets(token, TOKEN_LENGTH_MAX, configFile);

  //Remove trailing newline
  token[strcspn(token, "\r\n")] = '\0';
  
  fgets(buff, 6, configFile);
  refreshRate = atoi(buff);

  fgets(ip, IP_MAX, configFile);
  //Remove trailing newline
  ip[strcspn(ip, "\r\n")] = '\0';

  fgets(buff, 6, configFile);
  port = atoi(buff);

  fclose(configFile);


  return TRUE;

}

void showToStatus(char * action, char * data){

  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  sprintf(statusText, "%02d:%02d:%02d: %s %s\n",timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, action, data);
  OutputDebugString(statusText);

  //Remove newline
  statusText[strlen(statusText) - 1] = '\0'; 
  InvalidateRect(hwnd, &statusRect, FALSE);
}


void sendSlackMessage(HWND hwnd){
  DWORD bytesReceived;
  char messageFromBox[MAX_MESSAGE_FROM_BOX];
  char messageEscaped[MAX_MESSAGE_TO_SEND];

  GetWindowText(textField, messageFromBox, MAX_MESSAGE_FROM_BOX);

  escapes_encode(messageFromBox, messageEscaped);

  showToStatus("Posting:", messageEscaped);

  bytesReceived = restapi_sendMessageToChannel(ip, port, channelsList.channels[currentSelectedChannel].channelName, messageEscaped, token, lpGlobalMemory, allocatedMemorySize);

  if(bytesReceived > 0){
    SetWindowText(GetDlgItem(hwnd, TEXT_FIELD_ID ), "" );

  } else {
    showToStatus("Cannot send:", messageEscaped);
  }

}

void updateChannelsList(){

  DWORD bytesReceived;
  int i;

  showToStatus("Updating channels list", "");

  bytesReceived = restapi_getChannelList(ip, port, token, lpGlobalMemory, allocatedMemorySize);

  if(bytesReceived > 0){
    jsnparse_freeChannelList(&channelsList);
    jsnparse_parseChannelList(lpGlobalMemory, bytesReceived, &channelsList);

    SendMessage(GetDlgItem(hwnd, CHANNELS_BOX_ID), LB_RESETCONTENT, 0, 0);

    for (i = 0; i < channelsList.numChannels; i++){
      SendMessage(GetDlgItem(hwnd, CHANNELS_BOX_ID), LB_ADDSTRING, 0, (LPARAM) ((LPSTR) channelsList.channels[i].channelName));
    }
      
    channelsObtained = TRUE;
  } else {
    showToStatus("Cannot retrieve channels list", "");
  }
}

void updateUsersList(){

  DWORD bytesReceived;

  showToStatus("Updating users list", "");

  bytesReceived = restapi_getUsersList(ip, port, token, lpGlobalMemory, allocatedMemorySize);

  if(bytesReceived > 0){
    jsnparse_freeUserList(&usersList);
    jsnparse_parseUserList(lpGlobalMemory, bytesReceived, &usersList);

    usersObtained = TRUE;
  } else {
    showToStatus("Cannot retrieve users list", "");
  }
}

void updateChannelMessages(){
  DWORD bytesReceived;
  int i;
  char * messageText;

  showToStatus("Updating messages from:", channelsList.channels[currentSelectedChannel].channelName);

  bytesReceived = restapi_getChannelMessages(ip, port, channelsList.channels[currentSelectedChannel].channelID, token, lpGlobalMemory, allocatedMemorySize);

  if(bytesReceived > 0){
    jsnparse_freeMessagesList(&messagesList);
    jsnparse_parseMessageList(lpGlobalMemory, bytesReceived, &messagesList, MAX_MESSAGES_TO_PARSE);

    SendMessage(GetDlgItem(hwnd, LIST_BOX_ID), LB_RESETCONTENT, 0, 0);

    //Invert order of populating where newer messages appear below
    for (i = messagesList.numMessages - 1; i >= 0 ; --i){

      int userIndex;
      char * userToShow = messagesList.messages[i].userID;

      //If we can locate the userID, we display the username
      for(userIndex = 0; userIndex < usersList.numUsers; userIndex++){
        if (strcmp (userToShow, usersList.users[userIndex].userID) == 0){
          userToShow = usersList.users[userIndex].username;
          break;
        }
      }
     
      // Extra characters for the : and null terminator
      messageText = (char*) malloc(strlen(userToShow) + 3 + strlen(messagesList.messages[i].message) + 1);
      
      if(messageText != NULL){
        sprintf(messageText, "%s : %s", userToShow, messagesList.messages[i].message);
        SendMessage(GetDlgItem(hwnd, LIST_BOX_ID), LB_ADDSTRING, 0, (LPARAM) ((LPSTR) messageText));
        free(messageText);
      }
    }
      
  } else {
    showToStatus("Cannot retrieve messages list", "");
  }
}

void sendSingleShotUpdateTimer(HWND hwnd){
  SetTimer(hwnd, SINGLE_SHOT_TIMER_ID, 0, NULL);
}

/* Window procedure for our main window */
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

  HDC hdc;
  PAINTSTRUCT ps;

  char settingsText[80];

  switch (msg)
  {
    case WM_CREATE:
      showToStatus("Slack for Win 3.1 starting...", "");
      lpGlobalMemory = GlobalAllocPtr(GMEM_MOVEABLE, MAX_GLOBAL_MEM_ALLOCATION);
      allocatedMemorySize = GlobalSize(GlobalPtrHandle(lpGlobalMemory));

      hbrush = CreateSolidBrush(RGB(255, 255, 255));

      return 0;
    case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      sprintf(settingsText, "Proxy %s:%d, Refresh every %dms", ip, port, refreshRate);


      SetRect(&statusRect, 20, 357, 430, 374);
      FillRect(hdc, &statusRect, hbrush);
      DrawText(hdc, settingsText, strlen(settingsText), &statusRect, DT_LEFT | DT_NOCLIP);

      SetRect(&statusRect, 20, 380, 430, 397);
      FillRect(hdc, &statusRect, hbrush);
      DrawText(hdc, statusText, strlen(statusText), &statusRect, DT_LEFT | DT_NOCLIP);

      EndPaint(hwnd, &ps);

      return 0;

    case WM_TIMER:
      switch(wParam){
        case SINGLE_SHOT_TIMER_ID:
          KillTimer(hwnd, SINGLE_SHOT_TIMER_ID);
        case REFRESH_TIMER_ID:

        if(usersObtained){
          if(channelsObtained){
            updateChannelMessages();
          } else {
            updateChannelsList();
          }

        } else {
          updateUsersList();
        }

        return 0;
      }

    case WM_COMMAND:
    {

      if(((HWND) lParam) == channelsBox && (HIWORD(lParam) == LBN_SELCHANGE)){
        currentSelectedChannel = (WORD) SendMessage(channelsBox, LB_GETCURSEL, 0, 0L);

        showToStatus("Selected channel:", channelsList.channels[currentSelectedChannel].channelName);
        return 0;
      }

      if(((HWND)lParam) == sendButton && (HIWORD(wParam) == BN_CLICKED)){
        sendSlackMessage(hwnd);
        sendSingleShotUpdateTimer(hwnd);
        return 0;
      }

      switch (wParam)
      {
        case ID_HELP_ABOUT:
        {
          ShowAboutDialog(hwnd);
          return 0;
        }

        case ID_FILE_EXIT:
        {
          DestroyWindow(hwnd);
          return 0;
        }
      }
      break;
    }

    case WM_GETMINMAXINFO:
    {
      /* Prevent our window from being sized too small */
      MINMAXINFO FAR* minMax = (MINMAXINFO FAR*)lParam;
      minMax->ptMinTrackSize.x = 450;
      minMax->ptMinTrackSize.y = 450;

      return 0;
    }

    /* Item from system menu has been invoked */
    case WM_SYSCOMMAND:
    {
      WORD id = wParam;

      switch (id)
      {
        /* Show "about" dialog on about system menu item */
        case ID_HELP_ABOUT:
        {
          ShowAboutDialog(hwnd);
          return 0;
        }
      }
      break;
    }
    case WM_DESTROY:
    {
      
      DeleteObject(hbrush);
      GlobalFreePtr(lpGlobalMemory);
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}

/* Register a class for our main window */
BOOL RegisterMainWindowClass()
{
  WNDCLASS wc;

  /* Class for our main window */
  wc.style         = 0;
  wc.lpfnWndProc   = &MainWndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = g_hInstance;
  wc.hIcon         = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_APPICON));
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
  wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
  wc.lpszClassName = MainWndClass;

  return (RegisterClass(&wc)) ? TRUE : FALSE;
}

/* Create an instance of our main window */
HWND CreateMainWindow()
{
  /* Create instance of main window */
  hwnd = CreateWindowEx(0, MainWndClass, MainWndClass, WS_OVERLAPPEDWINDOW&~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 360, 360,
                             NULL, NULL, g_hInstance, NULL);

  if (hwnd)
  {
    /* Add "about" to the system menu */
    HMENU hSysMenu = GetSystemMenu(hwnd, FALSE);
    InsertMenu(hSysMenu, 5, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    InsertMenu(hSysMenu, 6, MF_BYPOSITION, ID_HELP_ABOUT, "About");


    channelsBox = CreateWindow("LISTBOX", "",  WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_HSCROLL, 20, 20, 100, 300, hwnd, CHANNELS_BOX_ID, g_hInstance, NULL);
    channelMessageBox = CreateWindow("LISTBOX", "",  WS_VSCROLL | WS_TABSTOP | WS_CHILD | WS_VISIBLE, 150, 20, 275, 300, hwnd, LIST_BOX_ID, g_hInstance, NULL);
  
    
    textField = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 325, 330, 25, hwnd, TEXT_FIELD_ID, g_hInstance, NULL);

    sendButton = CreateWindow( 
      "BUTTON",  // Predefined class; Unicode assumed 
      "Send",      // Button text 
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
      365,         // x position 
      325,         // y position 
      60,        // Button width
      25,        // Button height
      hwnd,     // Parent window
      NULL,       // No menu.
      g_hInstance, 
      NULL);      // Pointer not needed.
  
  }

  if(openAndProcessConfigFile(CONFIG_FILE_TO_OPEN)){
    if(refreshRate > 0){
      SetTimer(hwnd, REFRESH_TIMER_ID, refreshRate, NULL);
    }

  } else {
    MessageBox(hwnd, "Cannot open file w31slack.ini containing token, refresh rate (ms), HTTP Proxy IP, port", "Config File Error", MB_OK);
  }
  return hwnd;
}

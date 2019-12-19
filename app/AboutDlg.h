#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <windows.h>

/* Dialog procedure for our "about" dialog */
BOOL CALLBACK __export AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

/* Show our "about" dialog */
void ShowAboutDialog(HWND owner);

#endif

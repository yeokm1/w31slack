#ifndef MAINWND_H
#define MAINWND_H

#include <windows.h>

/* Window procedure for our main window */
LRESULT CALLBACK __export MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/* Register a class for our main window */
BOOL RegisterMainWindowClass(void);

/* Create an instance of our main window */
HWND CreateMainWindow(void);

#endif

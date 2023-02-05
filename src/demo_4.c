//
// Microsoft official demo
// https://learn.microsoft.com/zh-cn/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp
// Created by chris on 2023/1/18.
//

// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <string.h>
#include <tchar.h>
#include "head/win.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int DisplayConfirmSaveAsMessageBox();

LRESULT DisplayMyMessage(HINSTANCE hinst, HWND hwndOwner, LPSTR lpszMessage);

//https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-winmain
//https://learn.microsoft.com/zh-cn/windows/win32/learnwin32/winmain--the-application-entry-point
//基于 Windows 的图形应用程序的用户提供的入口点
int WINAPI WinMain(
        _In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPSTR lpCmdLine,
        _In_ int nCmdShow
) {
    WNDCLASSEX wcex;

    //https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-showwindow
    //最大化窗口
    nCmdShow = 3;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL,
                   _T("Call to RegisterClassEx failed!"),
                   _T("Windows Desktop Guided Tour"),
                   0);
        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    //创造窗口
    HWND hWnd = CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            szWindowClass,
            szTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            600, 400,
            NULL,
            NULL,
            hInstance,
            NULL
    );

    //创造按钮
    HWND button = CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "OK",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
            600,         // x position
            400,         // y position
            60,        // Button width
            40,        // Button height
            hWnd,     // Parent window
            NULL,       // No menu.
            (HINSTANCE) GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.


    //改变按钮文本
    //https://learn.microsoft.com/zh-cn/windows/win32/controls/create-a-command-link
    //SendMessage(button, WM_SETTEXT, 0, (LPARAM) "note");

    //DisplayConfirmSaveAsMessageBox();
    //DisplayMyMessage(hInstance, hWnd, lpCmdLine);

    if (!hWnd) {
        MessageBox(NULL,
                   _T("Call to CreateWindow failed!"),
                   _T("Windows Desktop Guided Tour"),
                   0);
        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hello, Windows desktop!");

    switch (message) {
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);

            // Here your application is laid out.
            // For this introduction, we just print out "Hello, Windows desktop!"
            // in the top left corner.
            TextOut(hdc,
                    5,
                    5,
                    greeting,
                    _tcslen(greeting));
            // End application-specific layout section.

            EndPaint(hWnd, &ps);
            break;
        }
            //退出提示
            //https://learn.microsoft.com/zh-cn/windows/win32/learnwin32/closing-the-window
            /*case WM_CLOSE: {
                if (MessageBox(hWnd, "Are you really quit?", "Application", MB_OKCANCEL) == IDOK) {
                    DestroyWindow(hWnd);
                }
                // Else: User canceled. Do nothing.
                return 0;
            }*/
            //退出不提示
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default: {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}

//显示消息框
//https://learn.microsoft.com/zh-cn/windows/win32/dlgbox/using-dialog-boxes
int DisplayConfirmSaveAsMessageBox() {
    int msgboxID = MessageBox(
            NULL,
            "temp.txt already exists.\nDo you want to replace it?",
            "Confirm Save As",
            MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES) {
        // TODO: add code
    }

    return msgboxID;
}

#define ID_HELP 150
#define ID_TEXT 200

LPWORD lpwAlign(LPWORD lpIn) {
    LPWORD ul;
    ul = lpIn;
    ul++;
    return ul;
}

LRESULT DisplayMyMessage(HINSTANCE hinst, HWND hwndOwner, LPSTR lpszMessage) {
    HGLOBAL hgbl;
    LPDLGTEMPLATE lpdt;
    LPDLGITEMTEMPLATE lpdit;
    LPWORD lpw;
    LPWSTR lpwsz;
    LRESULT ret;
    int nchar;

    hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
    if (!hgbl)
        return -1;

    lpdt = (LPDLGTEMPLATE) GlobalLock(hgbl);

    // Define a dialog box.

    lpdt->style = WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION;
    lpdt->cdit = 3;         // Number of controls
    lpdt->x = 10;
    lpdt->y = 10;
    lpdt->cx = 100;
    lpdt->cy = 100;

    lpw = (LPWORD) (lpdt + 1);
    *lpw++ = 0;             // No menu
    *lpw++ = 0;             // Predefined dialog box class (by default)

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "My Dialog", -1, lpwsz, 50);
    lpw += nchar;

    //-----------------------
    // Define an OK button.
    //-----------------------
    lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 10;
    lpdit->y = 70;
    lpdit->cx = 80;
    lpdit->cy = 20;
    lpdit->id = IDOK;       // OK button identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0080;        // Button class

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "OK", -1, lpwsz, 50);
    lpw += nchar;
    *lpw++ = 0;             // No creation data

    //-----------------------
    // Define a Help button.
    //-----------------------
    lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 55;
    lpdit->y = 10;
    lpdit->cx = 40;
    lpdit->cy = 20;
    lpdit->id = ID_HELP;    // Help button identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0080;        // Button class atom

    lpwsz = (LPWSTR) lpw;
    nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "Help", -1, lpwsz, 50);
    lpw += nchar;
    *lpw++ = 0;             // No creation data

    //-----------------------
    // Define a static text control.
    //-----------------------
    lpw = lpwAlign(lpw);    // Align DLGITEMTEMPLATE on DWORD boundary
    lpdit = (LPDLGITEMTEMPLATE) lpw;
    lpdit->x = 10;
    lpdit->y = 10;
    lpdit->cx = 40;
    lpdit->cy = 20;
    lpdit->id = ID_TEXT;    // Text identifier
    lpdit->style = WS_CHILD | WS_VISIBLE | SS_LEFT;

    lpw = (LPWORD) (lpdit + 1);
    *lpw++ = 0xFFFF;
    *lpw++ = 0x0082;        // Static class

    for (lpwsz = (LPWSTR) lpw; *lpwsz++ = (WCHAR) *lpszMessage++;);
    lpw = (LPWORD) lpwsz;
    *lpw++ = 0;             // No creation data

    GlobalUnlock(hgbl);
    ret = DialogBoxIndirect(hinst,
                            (LPDLGTEMPLATE) hgbl,
                            hwndOwner,
                            NULL);
    GlobalFree(hgbl);
    return ret;
}
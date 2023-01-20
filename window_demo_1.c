/*
 * https://learn.microsoft.com/zh-cn/windows/win32/learnwin32/windows-hello-world-sample
 * https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/begin/LearnWin32/HelloWorld/cpp/main.cpp
 */

//TODO 启动后会转圈圈，有待优化

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//https://learn.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-winmain
//基于 Windows 的图形应用程序的用户提供的入口点
int WINAPI WinMain(
        _In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPSTR lpCmdLine,
        _In_ int nCmdShow
//        HINSTANCE hInstance,
//        HINSTANCE hPrevInstance,
//        PWSTR pCmdLine,
//        int nCmdShow
) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Learn to Program Windows",    // Window text
            WS_OVERLAPPEDWINDOW,            // Window style
            // Size and position
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            600, //CW_USEDEFAULT
            400, //CW_USEDEFAULT
            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));

            EndPaint(hwnd, &ps);
        }
            return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
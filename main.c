#include <stdio.h>
#include <windows.h>

/**
如果需要显示中文，编码要选择GBK或GB2312
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

//基于 Windows 的图形应用程序的用户提供的入口点
int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR szCmdLine,
        int iCmdShow
) {
    static TCHAR szClassName[] = TEXT("Hello Window"); //窗口类名
    HWND hwnd; //窗口句柄
    MSG msg; //消息
    WNDCLASS wndclass; //窗口类

    hInst = hInstance;

    /**********第1步：注册窗口类**********/

    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //窗口风格
    wndclass.lpfnWndProc = WndProc; //窗口过程
    wndclass.cbClsExtra = 0; //暂时不需要理解
    wndclass.cbWndExtra = 0; //暂时不需要理解
    wndclass.hInstance = hInstance; //当前窗口句柄
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //窗口图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //鼠标样式
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //窗口背景画刷
    wndclass.lpszMenuName = NULL; //窗口菜单
    wndclass.lpszClassName = szClassName; //窗口类名

    //注册窗口
    RegisterClass(&wndclass);

    /*****第2步：创建窗口(并让窗口显示出来)*****/

    hwnd = CreateWindow(
            szClassName, //窗口类的名字
            TEXT("window"), //窗口标题（出现在标题栏）
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, //窗口风格
            CW_USEDEFAULT, //初始化时x轴的位置
            CW_USEDEFAULT, //初始化时y轴的位置
            600, //窗口宽度
            400, //窗口高度
            NULL, //父窗口句柄
            NULL, //窗口菜单句柄
            hInstance, //当前窗口的句柄
            NULL //不使用该值
    );

    /*hwnd = CreateWindow(
            "",
            "My first GUI window",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            100,
            100,
            200,
            200,
            NULL,
            NULL,
            NULL,
            NULL);*/

    if (hwnd == NULL) {
        // 打印错误，0x57f，Cannot find window
        printf("0x%x\n", GetLastError());
    }

    //显示窗口
    ShowWindow(hwnd, iCmdShow);

    //更新（绘制）窗口
    UpdateWindow(hwnd);

    /**********第3步：消息循环**********/

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); //翻译消息
        DispatchMessage(&msg); //分派消息
    }

    return msg.wParam;
}

/**********第4步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc; //设备环境句柄
    PAINTSTRUCT ps;
    RECT rect;

    static HFONT hFont;
    static HWND hBtn;

    switch (message) {
        //创建逻辑字体
        case WM_CREATE: {
            hFont = CreateFont(
                    -15, //高度
                    -7.5, //宽度
                    0,
                    0,
                    400, //一般这个值设为400
                    FALSE,//不带斜体
                    FALSE,//不带下划线
                    FALSE,//不带删除线
                    DEFAULT_CHARSET, //使用默认字符集
                    OUT_CHARACTER_PRECIS,
                    CLIP_CHARACTER_PRECIS, //这行参数不用管
                    DEFAULT_QUALITY, //默认输出质量
                    FF_DONTCARE, //不指定字体族
                    TEXT("微软雅黑") //字体名
            );
            //创建按钮控件
            hBtn = CreateWindow(
                    TEXT("button"), //按钮控件的类名
                    TEXT("这是按钮"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
                    220 /*X坐标*/,
                    20 /*Y坐标*/,
                    150 /*宽度*/,
                    50/*高度*/,
                    hwnd, (HMENU) 2 /*控件唯一标识符*/,
                    hInst,
                    NULL
            );
            SendMessage(hBtn, WM_SETFONT, (WPARAM) hFont, 0);//设置按钮字体
            break;
        }

            //窗口绘制消息
        case WM_PAINT: {
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            DrawText(
                    hdc,
                    TEXT("第一个窗口程序"),
                    -1,
                    &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER
            );

            EndPaint(hwnd, &ps);
            return 0;
        }

            //窗口销毁消息
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

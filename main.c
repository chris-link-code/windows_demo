#include <windows.h>

/**
https://blog.csdn.net/its4you/article/details/122716846
https://blog.csdn.net/its4you/article/details/122726939
�����Ҫ��ʾ���ģ�����Ҫѡ��GBK��GB2312
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
    static TCHAR szClassName[] = TEXT("HelloWin"); //��������
    HWND hwnd; //���ھ��
    MSG msg; //��Ϣ
    WNDCLASS wndclass; //������

    /**********��1����ע�ᴰ����**********/

    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //���ڷ��
    wndclass.lpfnWndProc = WndProc; //���ڹ���
    wndclass.cbClsExtra = 0; //��ʱ����Ҫ����
    wndclass.cbWndExtra = 0; //��ʱ����Ҫ����
    wndclass.hInstance = hInstance; //��ǰ���ھ��
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //����ͼ��
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //�����ʽ
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL; //���ڲ˵�
    wndclass.lpszClassName = szClassName; //��������

    //ע�ᴰ��
    RegisterClass(&wndclass);

    /*****��2������������(���ô�����ʾ����)*****/

    hwnd = CreateWindow(
            szClassName, //�����������
            TEXT("window"), //���ڱ��⣨�����ڱ�������
            WS_OVERLAPPEDWINDOW, //���ڷ��
            CW_USEDEFAULT, //��ʼ��ʱx���λ��
            CW_USEDEFAULT, //��ʼ��ʱy���λ��
            600, //���ڿ���
            400, //���ڸ߶�
            NULL, //�����ھ��
            NULL, //���ڲ˵����
            hInstance, //��ǰ���ڵľ��
            NULL //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd, iCmdShow);

    //���£����ƣ�����
    UpdateWindow(hwnd);

    /**********��3������Ϣѭ��**********/

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); //������Ϣ
        DispatchMessage(&msg); //������Ϣ
    }

    return msg.wParam;
}

/**********��4�������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HDC hdc; //�豸�������
    PAINTSTRUCT ps;
    RECT rect;
    switch (message) {
        //���ڻ�����Ϣ
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            DrawText(
                    hdc,
                    TEXT("��һ�����ڳ���"),
                    -1,
                    &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER
            );

            EndPaint(hwnd, &ps);
            return 0;

        //����������Ϣ
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}
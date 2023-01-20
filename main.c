#include <stdio.h>
#include <windows.h>

/**
�����Ҫ��ʾ���ģ�����Ҫѡ��GBK��GB2312
*/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

//���� Windows ��ͼ��Ӧ�ó�����û��ṩ����ڵ�
int WINAPI WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        PSTR szCmdLine,
        int iCmdShow
) {
    static TCHAR szClassName[] = TEXT("Hello Window"); //��������
    HWND hwnd; //���ھ��
    MSG msg; //��Ϣ
    WNDCLASS wndclass; //������

    hInst = hInstance;

    /**********��1����ע�ᴰ����**********/

    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW; //���ڷ��
    wndclass.lpfnWndProc = WndProc; //���ڹ���
    wndclass.cbClsExtra = 0; //��ʱ����Ҫ���
    wndclass.cbWndExtra = 0; //��ʱ����Ҫ���
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
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, //���ڷ��
            CW_USEDEFAULT, //��ʼ��ʱx���λ��
            CW_USEDEFAULT, //��ʼ��ʱy���λ��
            600, //���ڿ��
            400, //���ڸ߶�
            NULL, //�����ھ��
            NULL, //���ڲ˵����
            hInstance, //��ǰ���ڵľ��
            NULL //��ʹ�ø�ֵ
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
        // ��ӡ����0x57f��Cannot find window
        printf("0x%x\n", GetLastError());
    }

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

    static HFONT hFont;
    static HWND hBtn;

    switch (message) {
        //�����߼�����
        case WM_CREATE: {
            hFont = CreateFont(
                    -15, //�߶�
                    -7.5, //���
                    0,
                    0,
                    400, //һ�����ֵ��Ϊ400
                    FALSE,//����б��
                    FALSE,//�����»���
                    FALSE,//����ɾ����
                    DEFAULT_CHARSET, //ʹ��Ĭ���ַ���
                    OUT_CHARACTER_PRECIS,
                    CLIP_CHARACTER_PRECIS, //���в������ù�
                    DEFAULT_QUALITY, //Ĭ���������
                    FF_DONTCARE, //��ָ��������
                    TEXT("΢���ź�") //������
            );
            //������ť�ؼ�
            hBtn = CreateWindow(
                    TEXT("button"), //��ť�ؼ�������
                    TEXT("���ǰ�ť"),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,
                    220 /*X����*/,
                    20 /*Y����*/,
                    150 /*���*/,
                    50/*�߶�*/,
                    hwnd, (HMENU) 2 /*�ؼ�Ψһ��ʶ��*/,
                    hInst,
                    NULL
            );
            SendMessage(hBtn, WM_SETFONT, (WPARAM) hFont, 0);//���ð�ť����
            break;
        }

            //���ڻ�����Ϣ
        case WM_PAINT: {
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
        }

            //����������Ϣ
        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

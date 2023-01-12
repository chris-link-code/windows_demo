#include <stdio.h>
#include <windows.h>

//int main() {
//    printf("Hello, World!\n");
//    return 0;
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 调用API 函数MessageBox
    MessageBox(NULL, TEXT("Hello World!"), TEXT("window"), MB_OKCANCEL);
    return 0;
}
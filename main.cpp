#include "p_window.h"
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                   LPSTR lpstr, int nCmdLine) {

    window::Window wnd(WINDOW_WIDTH, WINDOW_HEIGHT, "test window");

    MSG msg = {0};

    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
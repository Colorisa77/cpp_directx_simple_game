#include "p_window.h"

namespace window {

    //WindowClass
    Window::WindowClass Window::WindowClass::wnd_class;

    Window::WindowClass::WindowClass() noexcept
    :hInstance_(GetModuleHandle(NULL)) {

        WNDCLASSEX wc = {0};

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = HandleMsgSetup;
        wc.cbWndExtra = 0;
        wc.cbClsExtra = 0;
        wc.hInstance = GetInstance();
        wc.hIcon = NULL;
        wc.hCursor = NULL;
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = GetName();
        wc.hIconSm = NULL;

        RegisterClassEx(&wc);
    }

    Window::WindowClass::~WindowClass() {
        UnregisterClass(wndClassName_, GetInstance());
    }

    const char * Window::WindowClass::GetName() noexcept {
        return wndClassName_;
    }

    HINSTANCE Window::WindowClass::GetInstance() noexcept {
        return wnd_class.hInstance_;
    }

    //Window
    Window::Window(int width, int height, const char* name) noexcept {
        RECT wr;

        wr.left = 100;
        wr.right = width + wr.left;
        wr.top = 100;
        wr.bottom = height + wr.top;

        AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

        hWnd_ = CreateWindow(
            WindowClass::GetName(), name,
            WS_CAPTION | WS_MINIMIZE | WS_SYSMENU,
            CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
            NULL, NULL, WindowClass::GetInstance(), this
            );

        ShowWindow(hWnd_, SW_SHOWDEFAULT);
    }

    Window::~Window() {
        DestroyWindow(hWnd_);
    }

    LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
        if(msg == WM_NCCREATE) {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

            return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
        Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
        switch(msg) {
            case WM_CLOSE:
                PostQuitMessage(0);
                return 0;
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

} // namespace window
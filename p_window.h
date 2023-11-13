#pragma once

#include "p_windows_simple.h"

namespace window {

    class Window {
        class WindowClass {
        public:
            static const char* GetName() noexcept;
            static HINSTANCE GetInstance() noexcept;
        private:
            WindowClass() noexcept;
            ~WindowClass();

            WindowClass& operator=(const WindowClass&) = delete;

            static constexpr const char* wndClassName_ = "Simple DirectX Game";
            static WindowClass wnd_class;
            HINSTANCE hInstance_;
        };

    public:
        Window(int width, int height, const char* name) noexcept;
        Window(const Window&) = delete;
        ~Window();

        Window& operator=(const Window&) = delete;
    private:
        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


        int width_;
        int height_;
        HWND hWnd_;
    };


} // namespace window
#if defined(_WIN32) || defined(_WIN64)

#include "KwWindow.hpp"

#include <iostream>

#include <windows.h>

namespace kwlib {

  KwWindowWin::KwWindowWin(const char* n, int w, int h, int _x, int _y) : name{n}, width{w}, height{h}, x{_y}, y{_y} {}

  void KwWindowWin::show() {
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = DefWindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = name;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0,
        CLASS_NAME,
        name,
        WS_OVERLAPPEDWINDOW,
        x, y, width, height,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!hwnd) {
      MessageBox(NULL, "Error creating window", "Error", MB_ICONERROR);
      return;
    }

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

}

#endif
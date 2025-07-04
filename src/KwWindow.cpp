#include "KwWindow.hpp"

#include <iostream>
#include <memory>

namespace kwlib {

  KwWindow::KwWindow(const char* n, int w, int h, int x, int y) {
    #if defined(__linux__)
      impl = std::make_unique<KwWindowUnix>(n, w, h, x, y);
    #elif defined(_WIN32) || defined(_WIN64)
      impl = std::make_unique<KwWindowWin>(n, w, h, x, y);
    #else
      #error "Unsupported platform."
    #endif
  }

  KwWindow::~KwWindow() = default;

  void KwWindow::show() {
    impl->show();
  }

}
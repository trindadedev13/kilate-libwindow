#ifndef __KWWINDOW_HPP__
#define __KWWINDOW_HPP__

#include <memory>

namespace kwlib {

struct KwWindowImpl;

struct KwWindow {
  KwWindow(const char* name, int width, int height, int x, int y);
  ~KwWindow();

  void show();

  private:
    std::unique_ptr<KwWindowImpl> impl;
};

struct KwWindowImpl {
  virtual ~KwWindowImpl() = default;
  virtual void show() = 0;
};

#if defined(_WIN32) || defined(_WIN64)

struct KwWindowWin : KwWindowImpl {
  KwWindowWin(const char* name, int width, int height, int x, int y);
  void show() override;

  private:
    const char* name;
    int width;
    int height;
    int x;
    int y;
};

#elif defined(__linux__)

struct KwWindowUnix : KwWindowImpl {
  KwWindowUnix(const char* name, int width, int height, int x, int y);
  void show() override;

  private:
    const char* name;
    int width;
    int height;
    int x;
    int y;
};

#endif

}

#endif
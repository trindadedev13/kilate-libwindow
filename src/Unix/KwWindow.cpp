#if defined(__linux__)

#include "KwWindow.hpp"

#include <iostream>

#include <X11/Xlib.h>

namespace kwlib {

  KwWindowUnix::KwWindowUnix(const char* n, int w, int h, int _x, int _y) : name{n}, width{w}, height{h}, x{_x}, y{_y} {}

  void KwWindowUnix::show() {
    Display* dpy = XOpenDisplay(NULL);
    if (!dpy) {
      fprintf(stderr, "Error: Could not open X11 display.\n");
      return;
    }

    int screen = DefaultScreen(dpy);
    Window win = XCreateSimpleWindow(
        dpy, RootWindow(dpy, screen),
        x, y, width, height, 1,
        BlackPixel(dpy, screen),
        WhitePixel(dpy, screen));

    XStoreName(dpy, win, name);
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    XEvent e;
    while (1) {
      XNextEvent(dpy, &e);
      if (e.type == KeyPress)
        break;
    }

    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
  }

}

#endif
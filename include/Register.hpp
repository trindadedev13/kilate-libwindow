#ifndef __REGISTER__
#define __REGISTER__

extern "C" {

  #include <kilate/native.h>

  klt_node* kw_open_window(klt_native_fndata*);
  klt_native_fnentry* kw_get_open_window_fnentry();

}

#endif
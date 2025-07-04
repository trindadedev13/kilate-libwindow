extern "C" {
  #include <kilate/native.h>
}

#include "Register.hpp"

extern "C" KILATE_NATIVE_REGISTER() {
  klt_native_register_fnentry(kw_get_open_window_fnentry());
}
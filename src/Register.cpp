#include <cstdlib>
#include <string.h>
#include <iostream>

#include "Register.hpp"
#include "KwWindow.hpp"
#include "Kilatepp/Native.hpp"

extern "C" {

  #include <kilate/native.h>

  klt_node* kw_open_window(klt_native_fndata* data) {
    if (data->params->size == 5) {
      std::string name = kilate::native::getFnDataString(data, 0);
      int width        = kilate::native::getFnDataNumber(data, 1);
      int height       = kilate::native::getFnDataNumber(data, 2);
      int x            = kilate::native::getFnDataNumber(data, 3);
      int y            = kilate::native::getFnDataNumber(data, 4);
      kwlib::KwWindow window{name.c_str(), width, height, x, y};
      window.show();
    }
    free(data);
    return NULL;
  }

  klt_native_fnentry* kw_get_open_window_fnentry() {
    // Required params
    klt_str_vector* reqParams = klt_vector_make(sizeof(klt_str*));
    kilate::native::addParam(reqParams, "string");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    kilate::native::addParam(reqParams, "number");
    klt_native_fnentry* entry =
        kilate::native::createFnEntry("kw_open_window",
                                      reqParams,
                                      kw_open_window);
    return entry;
  }

}
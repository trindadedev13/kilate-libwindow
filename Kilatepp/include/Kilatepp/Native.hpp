#ifndef __NATIVE_HPP__
#define __NATIVE_HPP__

#include <string>
#include <iostream>

extern "C" {
  #include <kilate/native.h>
}

namespace kilate {
  namespace native {
    /** These methods also checks the 'var' type. */
    /** Returns a string value from a param in klt_native_fndata */
    std::string getFnDataString(klt_native_fndata* data, size_t index);
    /** Returns a number value from a param in klt_native_fndata */
    int getFnDataNumber(klt_native_fndata* data, size_t index, bool* ok = nullptr);
    /** Returns a bool value from a param in klt_native_fndata */
    bool getFnDataBool(klt_native_fndata* data, size_t index, bool* ok = nullptr);

    /** Adds a param in params vector */
    void addParam(klt_str_vector* params, const std::string& param);
    /** Creates a klt_native_fnentry */
    klt_native_fnentry* createFnEntry(const std::string& name, klt_str_vector* reqParams, klt_native_fn fn);
  }
}

#endif
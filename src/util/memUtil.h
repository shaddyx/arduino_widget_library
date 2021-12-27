#pragma once
#include <pgmspace.h>

template <class T>
T read_pgm_value(const T & pgm_addr){
    T value;
    memcpy_P(&value, &pgm_addr, sizeof(T));
    return value;
}
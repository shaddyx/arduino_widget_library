#pragma once
#include "widget.h"
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
namespace widgetTools {
    std::shared_ptr<Widget>  build(const String &data, int size);
}
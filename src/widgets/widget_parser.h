#pragma once

#include "widget.h"
#include <Arduino.h>
namespace widgetTools {
    void parse(std::shared_ptr<Widget>  widget, const String &params);
}
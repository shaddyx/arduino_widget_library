#pragma once
#include "widget.h"
#include "widget_debug.h"
#include <collections/SimpleList.h>
#include <vector>
class Widget;
namespace widgetTools {
    int max(int a, int b);
    Widget * find_main(Widget * self);
    void stretch_main_direction(Widget * self);
    void stretch_second_direction(Widget * self);
    int calc_space_to_stretch(Widget * self);
    std::vector<Widget *> get_stretchable_children(Widget * self, bool hor);
};

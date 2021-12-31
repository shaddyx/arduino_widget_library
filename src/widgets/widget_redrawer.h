#pragma once
#include "widget.h"
#include "widget_debug.h"
#include <collections/SimpleList.h>
#include <vector>
class Widget;
namespace widgetTools {
    int max(int a, int b);
    std::shared_ptr<Widget>  find_main(std::shared_ptr<Widget>  self);
    void stretch_main_direction(std::shared_ptr<Widget>  self);
    void stretch_second_direction(std::shared_ptr<Widget>  self);
    int calc_space_to_stretch(std::shared_ptr<Widget>  self);
    std::vector<std::shared_ptr<Widget> > get_stretchable_children(std::shared_ptr<Widget>  self, bool hor);
};

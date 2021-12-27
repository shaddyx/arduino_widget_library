#include "widget.h"

namespace widgetTools{
    void render(Widget * self) {
        int x = 0;
        int y = 0;
        for (int i=0; i < self -> widgets.size(); i++){
            auto widget = self -> widgets[i];
            if (widget -> get_visible()){
                widget -> set_x(x);
                widget -> set_y(y);
                if (self -> get_horz()){
                    x += widget->get_w();
                } else {
                    y += widget->get_h();
                }
            }
        }
    }
}
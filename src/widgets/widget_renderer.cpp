#include "widget.h"

namespace widgetTools{
    int get_center(int w, int child_w){
        return (w - child_w) / 2;
    }

    void render(Widget * self) {
        int x = self -> get_dx();
        int y = self -> get_dy();
        for (auto widget: self -> widgets){
            if (widget -> get_visible()){
                widget -> set_x(x);
                widget -> set_y(y);
                if (self -> get_horz()){
                    x += widget->get_w();
                    if (widget -> get_centered()){
                        widget -> set_y(y + get_center(self -> get_inner_h(), widget -> get_h()));
                    }
                } else {
                    y += widget->get_h();
                    if (widget -> get_centered()){
                        widget -> set_x(x + get_center(self -> get_inner_w(), widget -> get_w()));
                    }
                }
            }
        }
    }
}
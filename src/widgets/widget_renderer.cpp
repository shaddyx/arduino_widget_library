#include "widget.h"

namespace widgetTools{
    int get_center(int w, int child_w){
        return (w - child_w) / 2;
    }
    
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
                    if (widget -> get_center()){
                        widget -> set_y(get_center(self -> get_inner_h(), widget -> get_h()));
                    }
                } else {
                    y += widget->get_h();
                    if (widget -> get_center()){
                        widget -> set_x(get_center(self -> get_inner_w(), widget -> get_w()));
                    }
                }
            }
        }
    }
}
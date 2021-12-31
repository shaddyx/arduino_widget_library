#include "widget.h"
#include "widget_debug.h"
namespace widgetTools {

    int max(int a, int b) {
        return a < b ? b : a;
    }

    int stretch_min_size_value(Widget * self, Widget * widget_element){
        return self -> get_horz() ? widget_element -> get_min_w() : widget_element -> get_min_h();
    }

    int stretch_size_value(Widget * self, Widget * widget_element){
        return self -> get_horz() ? widget_element -> get_w() : widget_element -> get_h();
    }

    int stretch_dx_value(Widget * self, Widget * widget_element){
        return self -> get_horz() ? widget_element -> get_full_dx() : widget_element -> get_full_dy();
    }

    void set_stretch_value(Widget * self, Widget * widget_element, int value){
        if (self -> get_horz()){
            widget_element -> set_w(value);
        } else {
            widget_element -> set_h(value);
        }
    }
    Widget * find_main(Widget * self){
        Widget * parent = self;
        while ((parent = parent -> parent) != NULL && !parent -> main){
        }
        return parent;
    }
    void stretch_main_direction(Widget * self) {
        
        //
        //  assuming we have all min sizes here
        //

        int lastInner = calc_space_to_stretch(self);
        int skipInner = 0;
        int skip_count = 0;
        bool foundSmaller;

        std::vector<Widget *> widgets_to_stretch = get_stretchable_children(self, self -> get_horz());
        dbg_d("widgets to stretch[%d]: %d, lastInner: %d, w:%d, h:%d, mw:%d, mh:%d, inner_w: %d", self -> get_id(), 
            widgets_to_stretch.size(), 
            lastInner, 
            self -> get_w(), 
            self -> get_h(), 
            self -> get_min_w(), 
            self -> get_min_h(), 
            self -> get_inner_w());
        do {
            foundSmaller = false;
            for (int i=0; i < widgets_to_stretch.size(); i++){
                int newSize = floor((lastInner - skipInner) / (widgets_to_stretch.size() - skip_count));
                auto widget = widgets_to_stretch[i];
                if (widget){
                    float ratio = widget -> percent / .100;
                    float sizeToApply = floor(newSize * ratio);
                    if (sizeToApply < stretch_min_size_value(self, widget) ){
                        dbg_d("Found smaller widget [%d]: minw: %d sizeToApply: %f, newSize: %d", widget -> get_id(), 
                        stretch_min_size_value(self, widget), 
                        sizeToApply, 
                        newSize);
                        set_stretch_value(self, widget, stretch_min_size_value(self, widget));
                        skipInner += stretch_size_value(self, widget);
                        foundSmaller = true;
                        widgets_to_stretch[i] = 0;
                        skip_count ++;
                    }
                }
            }
        } while (foundSmaller);
        //		
        //		setting new sizes for child nodes
        //
        if (widgets_to_stretch.size()){
            int lastValue = lastInner - skipInner;
            dbg_d("lastValue [%d] is: %d", self -> get_id(), lastValue);
            auto newSize = floor(lastValue / float(widgets_to_stretch.size() - skip_count));
            dbg_d("newSize [%d] is: %f, count: %d, skipCount: %d", self -> get_id(), newSize, widgets_to_stretch.size() - skip_count, skip_count);

            for (int i=0; i < widgets_to_stretch.size(); i++){
                auto widget = widgets_to_stretch[i];
                if (widget){
                    auto ratio = widget->percent / float(100);
                    dbg_d("ratio [%d]: %f", widget -> get_id(), ratio);
                    int sizeToApply = ceil(newSize * ratio);
                    if (widgets_to_stretch.size() - skip_count != i + 1){
                        dbg_d("setting widget w [%d]: sizeToApply: %d", widget -> get_id(), sizeToApply);
                        set_stretch_value(self, widget, max(stretch_min_size_value(self, widget), sizeToApply));
                        widget -> adapt_sizes();
                        lastValue -= stretch_size_value(self, widget);
                    } else {
                        dbg_d("setting last widget w [%d]: lastValue: %d", widget -> get_id(), lastValue);
                        set_stretch_value(self, widget, lastValue);
                        lastValue = 0;
                        widget -> adapt_sizes();
                    }
                }
            }
        }
    }
        
    void stretch_second_direction(Widget * self) {
        int size = self -> get_horz() ? self -> get_inner_h() : self -> get_inner_w();

        for (auto widget: self -> widgets){
            if (widget -> get_visible()){
                if (!self -> get_horz() && widget -> get_hs()){
                    widget->set_w(size);
                } else if (self -> get_horz() && widget -> get_vs()){
                    widget->set_h(size);
                }
            }
        }
    }
        
    int calc_space_to_stretch(Widget * self) {
        int space = self -> get_horz() ? self -> get_inner_w() : self -> get_inner_h();
        for (auto widget: self -> widgets){
            if (!widget -> get_visible()){
                continue;
            }
            if (self -> get_horz()){
                if (!widget -> get_hs()){
                    space -= widget -> get_w();
                }
            } else {
                if (!widget -> get_vs()){
                    space -= widget -> get_h();
                }
            }
        }
        return space;
    }

    std::vector<Widget *> get_stretchable_children(Widget * self, bool hor){
        std::vector<Widget *> list;
        list.reserve(self -> widgets.size());
        for (auto widget: self -> widgets){
            if (widget -> get_visible()){
                if ((hor && widget -> get_hs()) || (!hor && widget -> get_vs())){
                    list.push_back(widget);
                } 
            }
        }
        return list;
    }
};
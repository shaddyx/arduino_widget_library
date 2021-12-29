#pragma once
#include <collections/SimpleList.h>
#include "widget_debug.h"
#include <math.h>
#include "widget_redrawer.h"
#include "widget_renderer.h"
#include <pointers/SP.h>
#include <Arduino.h>
#include "widget_parser.h"
#include <vector>

using namespace widgetTools;

namespace {
    static int __id_counter = 0;
}
    #define setter_getter(type, name) \
        Widget * set_##name(type name) { \
            if (this->params.name != name){\
                this->params.name = name; \
            }\
        return this;\
        }\
        type get_##name() {return this -> params.name; }

    #define setter_getter_func(type, name, func) \
        Widget * set_##name(type name) { \
            if (this->params.name != name){\
                this->params.name = name; \
            }\
        return this;\
        } \
        type get_##name() func
    

struct WidgetParams{
    int id = __id_counter++;
    String name;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int min_w = 0;
    int min_h = 0;
    int px = 0;
    int py = 0;
    bool hs = false;
    bool vs = false;
    bool centered = false;
    bool visible = true;
    bool horz = true;
};

class Widget{
    public: 
        WidgetParams params;
        Widget * parent = 0;
        setter_getter(int, id);
        setter_getter(int, x);
        setter_getter(int, y);
        setter_getter_func(int, w, { return max(get_min_w(), params.w);});
        setter_getter_func(int, h, { return max(get_min_h(), params.h);});
        setter_getter_func(int, min_w, { return max(calculated_min_w, params.min_w); });
        setter_getter_func(int, min_h, { return max(calculated_min_h, params.min_h); });
        setter_getter(int, px);
        setter_getter(int, py);
        setter_getter(bool, hs);
        setter_getter(bool, vs);
        setter_getter(bool, centered);
        setter_getter(bool, visible);
        setter_getter(bool, horz);
        setter_getter(String, name);
        
        std::vector<Widget *> widgets;

        char percent = 100;
        bool updated = false;
        bool main = true;
        bool should_draw = true;
        Widget() {

        }
        
        Widget(const String &params){
            widgetTools::parse(this, params);
        }
        
        Widget * add(Widget &widget){
            return add(&widget);
        }

        Widget * add(Widget * widget){
            if (widget && widget != this){
                widget -> parent = this;
                widgets.push_back(widget);
            }
            return this;
        }
        
        void clear(){
            widgets.clear();
        }

        Widget * start(){
            return this;
        }

        Widget * get(int index){
            return widgets[index];
        }

        int get_abs_x(){
            int res = this -> get_x();
            Widget * parent = this;
            while ((parent = parent -> parent) != NULL){
                res += parent -> get_x();
            }

            return res;
        }

        int get_abs_y(){
            int res = this -> get_y();
            Widget * parent = this;
            while ((parent = parent -> parent) != NULL){
                res += parent -> get_y();
            }
            return res;
        }

        int get_abs_x1(){
            return get_abs_x() + get_w();
        }

        int get_abs_y1(){
            return get_abs_y() + get_h();
        }
        
        int get_inner_w(){
            return this -> get_w() - this->get_px() * 2;
        }

        int get_inner_h(){
            return this -> get_h() - this->get_py() * 2;
        }

        virtual void draw(){
        }
        
        void poll(){
            if (main){
                call_adapt_sizes();
                calc_min_sizes();
                recalc_sizes();
                call_adapt_sizes();
                call_render();
                call_draw();
            }
        }
        void call_adapt_sizes(){
            if (!get_visible()) {
                return;
            }
            adapt_sizes();
            for (auto widget: widgets){
                widget -> call_adapt_sizes();
            }
        }
        void call_render(){
            if (!get_visible()) {
                return;
            }
            for (auto widget: widgets){
                widget -> call_render();
            }
            render(this);
        }

        void recalc_sizes(){
            if (!get_visible()){
                dbg_d("skipping sizes recalculation due to invisibility[%d]", get_id());
                return;
            }
            adapt_sizes();
            stretch_main_direction(this);
            stretch_second_direction(this);
            for (auto widget: widgets){
            
                widget -> recalc_sizes();
            }
        }

        void adapt_sizes(){
            if (get_w() < get_min_w()){
                dbg_d("resizing width[%d] %d to %d", get_id(), get_w(), get_min_w());
            }
            if (get_h() < get_min_h()){
                dbg_d("resizing height[%d] %d to %d", get_id(), get_h(), get_min_h());
            }
            set_w(max(get_w(), get_min_w()));
            set_h(max(get_h(), get_min_h()));
        }

        Widget * find_by_name(const String &name){
            if (name == this->params.name){
                return this;
            }
            for (auto widget: widgets){
                auto res = widget->find_by_name(name);
                if (res){
                    return res;
                }
            }
            return 0;
        }

        private:
         
            int calculated_min_w = 0;
            int calculated_min_h = 0;

            void calc_min_sizes(){
                int internal_min_w = 0;
                int internal_min_h = 0;
                for (auto widget: widgets){
                    if (! widget -> get_visible()){
                        continue;
                    }
                    widget->calc_min_sizes();
                    dbg_d("Calculated inner[%d] minw: %d, minh: %d ", widget -> get_id(), widget -> get_min_w(), widget -> get_min_h());
                    if (get_horz()){
                        internal_min_w += widget->get_min_w();
                        internal_min_h = max(widget->get_min_h(), internal_min_h);
                    } else {
                        internal_min_h += widget->get_min_h();
                        internal_min_w = max(widget->get_min_w(), internal_min_w);
                    }
                    dbg_d("Calculated[%d] internal minw: %d, internal minh: %d ", get_id(), internal_min_w, internal_min_h);
                }
                calculated_min_w = internal_min_w + get_px() * 2;
                calculated_min_h = internal_min_h + get_py() * 2;
                if (!get_hs()){
                    calculated_min_w = max(calculated_min_w, params.w);
                }
                if (!get_vs()){
                    calculated_min_h = max(calculated_min_h, params.h);
                }
                //dbg_d("Calculated sum[%d]: minw: %d, minh: %d ", id, calculated_min_w, calculated_min_h);
            }

            void call_draw(){
                if (!get_visible()) {
                    return;
                }
                draw();
                for (auto widget: widgets){
                    widget -> call_draw();
                }
            }
};
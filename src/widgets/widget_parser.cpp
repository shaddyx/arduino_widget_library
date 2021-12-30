#include "widget.h"
#include <string.h>
#include <Arduino.h>
#include <str_util/str_util.h>


namespace widgetTools{
    
    void parse_token(Widget * widget, const String & param){
        auto name = str_util::get_left_token(param, ":");
        name.trim();
        auto value = str_util::get_right_token(param, ":");
        value.trim();
        if (name == "w"){
            dbg_d("setting width to: %s", value.c_str());
            widget -> set_w(str_util::parse_int(value));
        } else if (name == "h"){
            dbg_d("setting height to: %s", value.c_str());
            widget -> set_h(str_util::parse_int(value));
        } else if (name == "min_w"){
            dbg_d("setting min_w to: %s", value.c_str());
            widget -> set_min_w(str_util::parse_int(value));
        } else if (name == "min_h"){
            dbg_d("setting min_h to: %s", value.c_str());
            widget -> set_min_h(str_util::parse_int(value));
        } else if (name == "hs"){
            dbg_d("setting hs to: %s", value.c_str());
            widget -> set_hs(str_util::parse_bool(value));
        } else if (name == "vs"){
            dbg_d("setting vs to: %s", value.c_str());
            widget -> set_vs(str_util::parse_bool(value));
        } else if (name == "horz"){
            dbg_d("setting horz to: %s", value.c_str());
            widget -> set_horz(str_util::parse_bool(value));
        } else if (name == "dx"){
            dbg_d("setting horz to: %s", value.c_str());
            widget -> set_dx(str_util::parse_int(value));
        } else if (name == "dy"){
            dbg_d("setting horz to: %s", value.c_str());
            widget -> set_dy(str_util::parse_int(value));
        } else {
            dbg_d("ERROR: unknown property: %s", name);
        }

    }

    void parse(Widget * widget, const String &params){
        dbg_d("parsing string: %s", params.c_str());
        int number = str_util::token_count(params, ",");
        for (int i =0; i < number; i++){
            String token = str_util::get_token(params, ",", i);
            parse_token(widget, token);
        }
    }
}
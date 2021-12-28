#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include "widget.h"
#include "str_util/str_util.h"
#include <ArduinoJson.h>
namespace widgetTools {
    #define __WIDGET_JSON_PARSER_FILL_TEMPLATE(WIDGET,DOC,TYPE, NAME) if (DOC.containsKey(#NAME)) WIDGET -> set_##NAME(DOC[#NAME].as<TYPE>());
    
    Widget * build(JsonObject data){
        auto widget = new Widget();
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, w);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, h);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, min_w);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, min_h);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, px);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, int, py);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, bool, horz);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, bool, hs);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, bool, vs);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, bool, center);
        __WIDGET_JSON_PARSER_FILL_TEMPLATE(widget, data, String, name);

        if (data.containsKey("c")){
            dbg_d("Children exists")
            auto c = data["c"].as<JsonArray>();
            for(JsonVariant v : c) {
                auto child = build(v);
                widget->add(child);
            }
        }
        return widget;
    }

    Widget * build(const String &data, int size){
        DynamicJsonDocument doc(size);
        deserializeJson(doc, data.c_str());
        return build(doc.as<JsonObject>());
    }

    void destroy(Widget * widget){
        for (int i=0; i<widget -> widgets.size(); i++){
            destroy(widget ->widgets[i]);
        }
        delete widget;
    }
   
}
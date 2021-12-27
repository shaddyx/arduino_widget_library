{% extends "base_header.h" %}
{% block content %}
#include <pgmspace.h>
namespace {{img.name}}_image{
    int img_w = {{img.w}};
    int img_h = {{img.h}};
    int img_size = {{img.size}};
    const uint8_t img_data[] PROGMEM = {
        {% for value in img.data %}{% if (loop.index % 10 == 0) %}

        {% endif %}{{value}},{% endfor %}

    };
}

{% endblock %}

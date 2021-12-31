#include <unity.h>
#include "widgets/widget.h"
#include "widgets/widget_builder.h"
namespace {
    
    void test_redraw_vert_with_inner_hs(){
        String data(R""""({
        w:100,
        h:0,
        horz: false,
        c:[
            {
                name: "w1",
                hs:true,
                c:[{
                    min_h:20
                }]
            },
            {
                h: 50
            },
        ]
    }
    )"""");
        auto widget = widgetTools::build(data, 2048);
        widget->poll();
        TEST_ASSERT_EQUAL(70, widget -> get_h());
        TEST_ASSERT_EQUAL(20, widget -> find_by_name("w1") -> get_h());
        widgetTools::destroy(widget);
    }

}

void test_redraw_main(){
    UNITY_BEGIN();
    RUN_TEST(test_redraw_vert_with_inner_hs);
    UNITY_END();
}
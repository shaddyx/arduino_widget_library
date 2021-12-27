#include <unity.h>
#include "widgets/widget.h"
#include "widgets/widget_builder.h"
namespace {
   void test_get_abs(){
       String data(R""""({
        w:10,
        h:20,
        c:[{
            w:100,
            h:100,
            name: "test2"
        }, {
            w:15,
            h:15,
            c:[
                {
                    name: "test1",
                    w: 20,
                    h: 50
                }
            ]

        }]
    }
    )"""");
    auto widget = widgetTools::build(data, 2048);
    widget->poll();
    TEST_ASSERT_EQUAL(100, widget -> find_by_name("test1")->get_abs_x());
    TEST_ASSERT_EQUAL(0, widget -> find_by_name("test1")->get_abs_y());
   }
}
void test_abs_main(){
    UNITY_BEGIN();
    RUN_TEST(test_get_abs);
    UNITY_END();
}
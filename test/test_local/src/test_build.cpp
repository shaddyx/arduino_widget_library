#include "widgets/widget.h"
#include "widgets/widget_parser.h"
#include "widgets/widget_builder.h"
#include <unity.h>
#include <Arduino.h>

void test_build(){
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
            name: "test1"
        }]
    }
    )"""");
    auto widget = widgetTools::build(data, 2048);
    TEST_ASSERT_EQUAL(10, widget -> get_w());
    TEST_ASSERT_EQUAL(20, widget -> get_h());
    TEST_ASSERT_EQUAL(2, widget -> widgets.size());
    TEST_ASSERT_EQUAL(100, widget -> widgets[0] -> get_w());
    TEST_ASSERT_EQUAL(100, widget -> widgets[0] -> get_h());

    auto test1 = widget -> find_by_name("test2");
    TEST_ASSERT_TRUE(test1);
    TEST_ASSERT_EQUAL_STRING("test2", test1 -> get_name().c_str());
}
void test_build_main(){
    RUN_TEST(test_build);
}


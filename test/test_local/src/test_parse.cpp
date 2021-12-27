#include "widgets/widget.h"
#include "widgets/widget_parser.h"
#include <unity.h>
namespace {
    Widget test_widget;
}
void test_parse_values(){
    widgetTools::parse(&test_widget, "w:123, h:10");
    TEST_ASSERT_EQUAL(123, test_widget.get_w());
    TEST_ASSERT_EQUAL(10, test_widget.get_h());

    Widget test_widget1("w:234, h:34");
    TEST_ASSERT_EQUAL(234, test_widget1.get_w());
    TEST_ASSERT_EQUAL(34, test_widget1.get_h());
    
}
void test_parse_main(){
    RUN_TEST(test_parse_values);
}


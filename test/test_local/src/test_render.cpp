#include <unity.h>
#include "widgets/widget.h"
namespace {
    Widget widget;
    Widget widget4;
    Widget widget5;

    void generate(){
        widget.start()
            -> set_w(120)
            -> set_h(120)
            -> set_min_w(10)
            -> set_min_h(10)
            -> set_horz(true)
            -> set_hs(false);
        widget4.start()
            -> set_hs(true);

        widget5.start()
            ->set_min_w(10)
            ->set_min_h(10)
            ->set_hs(false);
        widget.clear();
        widget.add(&widget4);
        widget.add(&widget5);
    }


    void test_widget(){
        generate();
        widget.set_horz(true);
        widget.get(0)->set_min_w(10);
        widget.get(0)->set_min_h(10);
        widget.poll();
        TEST_ASSERT_EQUAL(0, widget4.get_x());
        TEST_ASSERT_EQUAL(110, widget5.get_x());
    }
}

void test_render_main(){
    UNITY_BEGIN();
    RUN_TEST(test_widget);
    UNITY_END();
}
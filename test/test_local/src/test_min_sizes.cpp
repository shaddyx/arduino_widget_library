#include <unity.h>
#include "widgets/widget.h"

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
        -> set_hs(true)
        -> set_vs(true);
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
    dbg_d("minw: %d minh: %d\n", widget.get_min_w(), widget.get_min_h());
    TEST_ASSERT_EQUAL(20, widget.get_min_w());
    TEST_ASSERT_EQUAL(10, widget.get_min_h());
}

void test_widget_vertical(){
    generate();
    widget.set_horz(false);
    widget.get(0)->set_min_w(15);
    widget.get(0)->set_min_h(15);

    widget.poll();
    dbg_d("minw: %d minh: %d\n", widget.get_min_w(), widget.get_min_h());
    TEST_ASSERT_EQUAL(15, widget.get_min_w());
    TEST_ASSERT_EQUAL(25, widget.get_min_h());
}


void test_widget_margin(){
    generate();
    widget.set_w(0);
    widget.set_h(0);
    widget.set_px(5);
    widget.set_py(5);
    widget.set_horz(true);
    widget.get(0)->set_min_w(20);
    widget.get(0)->set_min_h(25);

    widget.poll();
    dbg_d("minw: %d minh: %d\n", widget.get_min_w(), widget.get_min_h());
    TEST_ASSERT_EQUAL(40, widget.get_min_w());
    TEST_ASSERT_EQUAL(35, widget.get_min_h());
}

void test_widget_sizes(){
    generate();
    widget.set_w(0);
    widget.set_h(0);
    widget.set_px(5);
    widget.set_py(5);
    widget.set_horz(true);
    widget.get(0)->set_min_w(20);
    widget.get(0)->set_min_h(25);

    widget.poll();
    dbg_d("w: %d h: %d\n", widget.get_w(), widget.get_h());
    TEST_ASSERT_EQUAL(40, widget.get_w());
    TEST_ASSERT_EQUAL(35, widget.get_h());
}

void test_min_sizes_main(){
    UNITY_BEGIN();
    RUN_TEST(test_widget);
    RUN_TEST(test_widget_vertical);
    RUN_TEST(test_widget_margin);
    RUN_TEST(test_widget_sizes);
    UNITY_END();
}
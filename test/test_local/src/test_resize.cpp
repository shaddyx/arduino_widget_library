#include <unity.h>
#include "widgets/widget.h"
namespace {
    Widget widget1;
    Widget widget2;
    Widget widget3;

    void test_widget_resize_horz(){
        widget1.set_horz(true);
        widget1.set_w(10);
        widget1.set_h(10);
        widget1.set_px(3);
        widget1.set_py(5);
        
        widget2.set_min_w(10);
        widget2.set_min_h(10);
        widget2.set_hs(true);
                
        widget3.set_min_w(10);
        widget3.set_min_h(10);
        widget3.set_hs(true);
        widget1.clear();
        widget1.add(&widget2);
        widget1.add(&widget3);
        widget1.poll();
        TEST_ASSERT_EQUAL(26, widget1.get_w());
        TEST_ASSERT_EQUAL(20, widget1.get_h()); //2 children min width + parent padding * 2
    }

    Widget widget4;
    Widget widget5;
    Widget widget6;
    Widget widget7;

    void test_widget_resize_vert(){
        widget4.set_horz(false);
        widget4.set_w(10);
        widget4.set_h(10);
        widget4.set_px(3);
        widget4.set_py(5);
        
        widget5.set_min_w(10);
        widget5.set_min_h(10);
        widget5.set_vs(true);
        widget5.set_hs(true);
                
        widget6.set_min_w(10);
        widget6.set_min_h(10);
        widget6.set_vs(true);
        widget6.set_hs(true);
        widget4.clear();
        widget4.add(&widget2);
        widget4.add(&widget3);
        widget4.poll();
        TEST_ASSERT_EQUAL(16, widget4.get_w());
        TEST_ASSERT_EQUAL(30, widget4.get_h()); //2 children min width + parent padding * 2
    }

    Widget widget8;
    Widget widget9;
    Widget widget10;

    void test_widget_resize_horz_big_parent(){
       
        widget8.set_id(1000);
        widget8.set_horz(true);
        widget8.set_w(100);
        widget8.set_h(200);
        widget8.set_px(3);
        widget8.set_py(5);
        
        widget9.set_min_w(10);
        widget9.set_min_h(10);
        widget9.set_vs(true);
        widget9.set_hs(true);
                
        widget10.set_min_w(10);
        widget10.set_min_h(10);
        widget10.set_vs(true);
        widget10.set_hs(true);
        widget8.clear();
        widget8.add(&widget9);
        widget8.add(&widget10);
        widget8.poll();
        TEST_ASSERT_EQUAL((100 - 6) / 2, widget9.get_w());
        TEST_ASSERT_EQUAL(190, widget9.get_h()); //2 children min width + parent padding * 2
    }

    void test_many_children(){
        Widget widgetA;
        Widget widgetB;
        Widget widgetC;
        Widget widgetD;
        widgetA.start()
            -> add(& widgetB)
            -> add(& widgetC)
            -> add(& widgetD)
            -> set_horz(false)
            -> set_w(100)
            -> set_h(1000);

            widgetB.start()
                -> set_vs(true)
                -> set_hs(false)
                -> set_w(230);
            
            widgetC.start()
                -> set_vs(false)
                -> set_hs(false)
                -> set_h(40)
                -> set_w(130);

            widgetD.start()
                -> set_vs(true)
                -> set_hs(true)
                -> set_w(1);

        widgetA.poll();
        TEST_ASSERT_EQUAL(230, widgetA.get_min_w());

        TEST_ASSERT_EQUAL(480, widgetB.get_h());
        TEST_ASSERT_EQUAL(40, widgetC.get_h());
        TEST_ASSERT_EQUAL(480, widgetD.get_h());

        TEST_ASSERT_EQUAL(230, widgetB.get_w());
        TEST_ASSERT_EQUAL(130, widgetC.get_w());
        TEST_ASSERT_EQUAL(230, widgetD.get_w());

    }
    void test_resize_left_smaller_min_w(){
          Widget widgetA;
        Widget widgetB;
        Widget widgetC;
        widgetA.start()
            -> add(& widgetB)
            -> add(& widgetC)
            -> set_horz(true)
            -> set_w(100)
            -> set_h(50);

            widgetB.start()
                -> set_hs(true)
                -> set_min_w(10);
            
            widgetC.start()
                -> set_hs(true)
                -> set_min_w(70);
        widgetA.poll();
        TEST_ASSERT_EQUAL(70, widgetC.get_w());
        TEST_ASSERT_EQUAL(30, widgetB.get_w());
        TEST_ASSERT_EQUAL(100, widgetA.get_w());
    }

      void test_resize_left_smaller_min_w_gigant(){
          Widget widgetA;
        Widget widgetB;
        Widget widgetC;
        widgetA.start()
            -> add(& widgetB)
            -> add(& widgetC)
            -> set_horz(true)
            -> set_w(100)
            -> set_h(50);

            widgetB.start()
                -> set_hs(true)
                -> set_min_w(10);
            
            widgetC.start()
                -> set_hs(true)
                -> set_min_w(70);
        widgetA.poll();
        TEST_ASSERT_EQUAL(70, widgetC.get_w());
        TEST_ASSERT_EQUAL(30, widgetB.get_w());
        TEST_ASSERT_EQUAL(100, widgetA.get_w());
    }
}
void test_resize_main(){
    UNITY_BEGIN();
    RUN_TEST(test_widget_resize_horz);
    RUN_TEST(test_widget_resize_vert);
    RUN_TEST(test_widget_resize_horz_big_parent);
    RUN_TEST(test_many_children);
    RUN_TEST(test_resize_left_smaller_min_w);
    UNITY_END();
}
#include <unity.h>
#include "widgets/widget.h"
#include "widgets/widget_redrawer.h"
#include <vector>
namespace {
   void test_get_stretchable_children(){
        Widget main("w:1000;horz:true");
        Widget a1("w:10,hs:true,vs:false");
        Widget a2("w:20,hs:true,vs:false");
        main.add(a1);
        main.add(a2);
        auto res = widgetTools::get_stretchable_children(&main, true);
        TEST_ASSERT_EQUAL(2, res.size());
        res = widgetTools::get_stretchable_children(&main, false);
        TEST_ASSERT_EQUAL(0, res.size());
   }

   void test_calc_space_to_stretch(){
        Widget main("w:1000;horz:true");
        Widget a1("w:10,hs:true,vs:false");
        Widget a2("w:20,hs:true,vs:false,min_w:10");
        main.add(a1);
        main.add(a2);
        auto res = widgetTools::calc_space_to_stretch(&main);
        TEST_ASSERT_EQUAL(1000, res);
   }

   void test_calc_space_to_stretch_vert(){
        Widget main("h:1000,horz:false,min_h:30");
        Widget a1("h:10,hs:false,vs:true");
        Widget a2("h:20,hs:false,vs:true");
        main.add(a1);
        main.add(a2);
        auto res = widgetTools::calc_space_to_stretch(&main);
        TEST_ASSERT_EQUAL(1000, res);
   }

   void test_calc_space_to_stretch_negative(){
        Widget main("h:1000;horz:false,min_h:30");
        Widget a1("h:10,hs:false,vs:true");
        Widget a2("h:20,hs:false,vs:true");
        main.add(a1);
        main.add(a2);
        auto res = widgetTools::calc_space_to_stretch(&main);
        TEST_ASSERT_EQUAL(1000, res);
   }
}
void test_widget_utils_main(){
    UNITY_BEGIN();
    RUN_TEST(test_get_stretchable_children);
    RUN_TEST(test_calc_space_to_stretch);
    RUN_TEST(test_calc_space_to_stretch_vert);
    RUN_TEST(test_calc_space_to_stretch_negative);
    UNITY_END();
}
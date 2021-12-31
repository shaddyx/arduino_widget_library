#include <unity.h>
#include "widgets/widget.h"
#include "widgets/widget_redrawer.h"
#include <vector>
namespace {
   void test_get_stretchable_children(){
        std::shared_ptr<Widget> main(new Widget("w:1000;horz:true"));
        std::shared_ptr<Widget> a1(new Widget("w:10,hs:true,vs:false"));
        std::shared_ptr<Widget> a2(new Widget("w:20,hs:true,vs:false"));
        main->add(a1);
        main->add(a2);
        auto res = widgetTools::get_stretchable_children(main, true);
        TEST_ASSERT_EQUAL(2, res.size());
        res = widgetTools::get_stretchable_children(main, false);
        TEST_ASSERT_EQUAL(0, res.size());
   }

   void test_calc_space_to_stretch(){
        std::shared_ptr<Widget> main(new Widget("w:1000;horz:true"));
        std::shared_ptr<Widget> a1(new Widget("w:10,hs:true,vs:false"));
        std::shared_ptr<Widget> a2(new Widget("w:20,hs:true,vs:false,min_w:10"));
        
        main -> add(a1);
        main -> add(a2);
        auto res = widgetTools::calc_space_to_stretch(main);
        TEST_ASSERT_EQUAL(1000, res);
   }
}
void test_widget_utils_main(){
    UNITY_BEGIN();
    RUN_TEST(test_get_stretchable_children);
    RUN_TEST(test_calc_space_to_stretch);
    UNITY_END();
}
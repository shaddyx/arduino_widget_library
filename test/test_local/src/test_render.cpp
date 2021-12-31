#include <unity.h>
#include "widgets/widget.h"
#include "widgets/widget_builder.h"
namespace {
    std::shared_ptr<Widget> widget(new Widget());
    std::shared_ptr<Widget> widget4(new Widget());
    std::shared_ptr<Widget> widget5(new Widget());

    void generate(){
        widget
            -> set_w(120)
            -> set_h(120)
            -> set_min_w(10)
            -> set_min_h(10)
            -> set_horz(true)
            -> set_hs(false);
        widget4
            -> set_hs(true);

        widget5
            ->set_min_w(10)
            ->set_min_h(10)
            ->set_hs(false);
        widget->clear();
        widget->add(widget4);
        widget->add(widget5);
    }


    void test_widget(){
        generate();
        widget->set_horz(true);
        widget->get(0)->set_min_w(10);
        widget->get(0)->set_min_h(10);
        widget->poll();
        TEST_ASSERT_EQUAL(0, widget4->get_x());
        TEST_ASSERT_EQUAL(110, widget5->get_x());
    }

    void test_multiple_children(){
        String data(R""""({
        w:100,
        h:200,
        c:[
            {
                hs:true,
                vs:true,
                c:[{
                    hs:true,
                    vs:true,
                    name: "test2"
                }, {
                    hs:true,
                    vs:true,
                    name: "test1"
                }]
            }
        ]
    }
    )"""");
        auto widget = widgetTools::build(data, 2048);
        widget->poll();
        TEST_ASSERT_EQUAL(50, widget -> find_by_name("test1")->get_x());
    }

    void test_center(){
        String data(R""""({
            w:100,
            h:200,
            c:[
                {
                    name: "test1", 
                    w: 20,
                    h:20,
                    centered: true
                }
            ]
        }
        )"""");
        auto widget = widgetTools::build(data, 2048);
        widget->poll();
        TEST_ASSERT_EQUAL(90, widget -> find_by_name("test1")->get_y());
    }
}

void test_render_main(){
    UNITY_BEGIN();
    RUN_TEST(test_widget);
    RUN_TEST(test_multiple_children);
    RUN_TEST(test_center);
    UNITY_END();
}
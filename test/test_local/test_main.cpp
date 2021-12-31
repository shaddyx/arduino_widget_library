#include <unity.h>
#include "widgets/widget.h"
#include "src/test_min_sizes.h"
#include "src/test_resize.h"
#include "src/test_render.h"
#include "src/test_parse.h"
#include "src/test_widget_utils.h"
#include "src/test_build.h"
#include "src/test_abs.h"
#include "src/test_redraw.h"

int main(){
    test_min_sizes_main();
    test_resize_main();
    test_render_main();
    test_parse_main();
    test_widget_utils_main();
    test_build_main();
    test_abs_main();
    test_redraw_main();
}

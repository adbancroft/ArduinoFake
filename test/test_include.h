#ifdef UNIT_TEST
#include "unity_filename_helper.h"

namespace IncludeTest
{

    void test_empty(void)
    {
        int PROGMEM a = 1;
    }

    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(IncludeTest::test_empty);
    }
}

#endif

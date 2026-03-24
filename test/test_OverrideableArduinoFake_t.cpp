#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

struct IDummy
{
    virtual void foo(void) { }
};

struct IArduino
{
    virtual void bar(void) {}
};

static void test_getFake(void)
{
    SimpleArduinoFake::details::FakeOverride_t overrides;
    SimpleArduinoFake::details::OverrideableArduinoFake_t<IDummy> subject(overrides);

    // No override, should get the real fake
    IArduino proxy;
    TEST_ASSERT_EQUAL_PTR(&subject.get(), subject.getFake<IArduino>(&proxy));

    // Should return the alternate, since it's now overriden
    SimpleArduinoFake::details::ArduinoFake_t<IArduino> alternateFake;
    overrides.setOverride(&proxy, &alternateFake);
    TEST_ASSERT_EQUAL_PTR(&alternateFake.get(), subject.getFake<IArduino>(&proxy));
}

namespace OverrideableArduinoFakeTTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_getFake);
    }
}

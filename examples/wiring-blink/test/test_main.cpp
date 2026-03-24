#include <ArduinoFake.h>
#include <unity.h>

using namespace fakeit;

void test_setup(void)
{
    When(Method(ArduinoFake::getContext()._Function, pinMode)).Return();

    setup();

    Verify(Method(ArduinoFake::getContext()._Function, pinMode).Using(LED_BUILTIN, OUTPUT)).Once();
}

void test_loop(void)
{
    When(Method(ArduinoFake::getContext()._Function, digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake::getContext()._Function, delay)).AlwaysReturn();

    loop();

    Verify(Method(ArduinoFake::getContext()._Function, digitalWrite).Using(LED_BUILTIN, HIGH)).Once();
    Verify(Method(ArduinoFake::getContext()._Function, digitalWrite).Using(LED_BUILTIN, LOW)).Once();
    Verify(Method(ArduinoFake::getContext()._Function, delay).Using(100)).Exactly(2_Times);
}

void setUp(void)
{
    ArduinoFake::getContext().Reset();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_setup);
    RUN_TEST(test_loop);

    UNITY_END();

    return 0;
}
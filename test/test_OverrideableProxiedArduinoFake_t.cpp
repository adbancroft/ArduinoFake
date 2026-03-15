#include <Arduino.h>
#include <unity.h>

using namespace fakeit;

struct IDummy
{
    virtual void foo(void) { }
};

struct IArduino
{
    virtual void bar(void) {}
};

struct IDummyProxy : public IArduino
{
    IDummy *_dummy;
    IDummy* getFake(void) { return _dummy; }

    virtual void bar(void) override {}
};

static void test_getFake(void)
{
    FakeOverride_t overrides;
    OverrideableProxiedArduinoFake_t<IDummy, IDummyProxy> subject(overrides);

    // No override, should get the proxy fake
    IDummyProxy proxy;
    TEST_ASSERT_EQUAL_PTR(proxy.getFake(), subject.getFake<IArduino>(&proxy));

    // Should return the alternate, since it's now overriden
    fakeit::Mock<IDummy> alternateFake;
    overrides.setOverride(&proxy, &alternateFake);
    TEST_ASSERT_EQUAL_PTR(&alternateFake.get(), subject.getFake<IArduino>(&proxy));
}

namespace OverrideableProxiedArduinoFakeTTest
{
    void run_tests(void)
    {
        RUN_TEST(test_getFake);
    }
}

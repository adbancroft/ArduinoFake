#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_single_instance(void)
{
    SimpleArduinoFake::Context* context1 = &SimpleArduinoFake::getContext();
    SimpleArduinoFake::Context* context2 = &SimpleArduinoFake::getContext();

    TEST_ASSERT_NOT_NULL(context1);
    TEST_ASSERT_NOT_NULL(context2);

    TEST_ASSERT_EQUAL(context1, context2);
}

template <typename FakeMethod>
void assert_test_reset(FakeMethod fakeMethod, std::function<void(void)> realMethod)
{
    Verify(fakeMethod).Never();

    // Call the "real" method...
    realMethod();
    // ...which should call the faked method
    Verify(fakeMethod).Once();

    // Reset all fakes
    SimpleArduinoFake::getContext().Reset();
    
    try {
        // This should throw an exception...
        realMethod(); 
        // ...fail the test if not.
        TEST_FAIL();
    }
    catch (fakeit::FakeitException &e) {
        Verify(fakeMethod).Never();
    }
}

static void test_reset_function(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._Function, millis);
    When(method).AlwaysReturn(101L);
    assert_test_reset(method, []() { (void)millis(); });
}

static void test_reset_print(void)
{
    auto method = OverloadedMethod(SimpleArduinoFake::getContext()._Print, print, size_t(const char[]));
    When(method).AlwaysDo([](const char *str) {
        std::cout << str;
        return strlen(str);
    });
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._Print.getFake())->print("abc"); });
}

static void test_reset_serial(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._Serial, end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._Serial.getFake())->end(); });
}

static void test_reset_wire(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._Wire, end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._Wire.getFake())->end(); });
}

static void test_reset_stream(void)
{
    auto method = OverloadedMethod(SimpleArduinoFake::getContext()._Stream, find, bool(const char *));
    When(method).AlwaysReturn(false);
    assert_test_reset(method, []() { 
        char toFind[] = "abc";
        (SimpleArduinoFake::getContext()._Stream.getFake())->find(toFind); 
    });
}

static void test_reset_client(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._Client, available);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._Client.getFake())->available(); });
}

static void test_reset_spi(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._SPI, end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._SPI.getFake())->end(); });
}

static void test_reset_eeprom(void)
{
    auto method = Method(SimpleArduinoFake::getContext()._EEPROM, length);
    When(method).AlwaysReturn(0xffff);
    assert_test_reset(method, []() { (SimpleArduinoFake::getContext()._EEPROM.getFake())->length(); });
}

static void test_reset(void)
{
#if defined(__MINGW64__)
    TEST_IGNORE_MESSAGE("Crashes under Mingw64");
#else
    RUN_TEST(test_reset_function);
    RUN_TEST(test_reset_serial);
    RUN_TEST(test_reset_wire);
    RUN_TEST(test_reset_stream);
    RUN_TEST(test_reset_client);
    RUN_TEST(test_reset_print);
    RUN_TEST(test_reset_spi);
    RUN_TEST(test_reset_eeprom);
#endif
}

static void test_function_mock(void)
{
    SimpleArduinoFake::details::FunctionFake* i1 = SimpleArduinoFake::getContext()._Function.getFake();
    SimpleArduinoFake::details::FunctionFake* i2 = SimpleArduinoFake::getContext()._Function.getFake();

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_print_mock(void)
{
    Print* i1 = SimpleArduinoFake::getContext()._Print.getFake();
    Print* i2 = SimpleArduinoFake::getContext()._Print.getFake();

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_stream_mock(void)
{
    Stream* i1 = SimpleArduinoFake::getContext()._Stream.getFake();
    Stream* i2 = SimpleArduinoFake::getContext()._Stream.getFake();

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_serial_mock(void)
{
    Serial_* i1 = SimpleArduinoFake::getContext()._Serial.getFake();
    Serial_* i2 = SimpleArduinoFake::getContext()._Serial.getFake();

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_unknown_instance_exception(void)
{
    fakeit::Mock<Serial_> fake;

    try {
        SimpleArduinoFake::getContext()._Serial.getFake(&fake.get());
    } catch (const std::runtime_error& e) {
        TEST_ASSERT_EQUAL_STRING("Unknown instance", e.what());
    }
}

static void test_getter_overload_with_proxy(void)
{
    Serial_* serial(SimpleArduinoFake::getContext()._Serial.getFake());
    Print* serialPrintFake = SimpleArduinoFake::getContext()._Serial.getFake(serial);

    TEST_ASSERT_EQUAL(SimpleArduinoFake::getContext()._Serial.getFake(), serialPrintFake);
    Print* printFake = SimpleArduinoFake::getContext()._Print.getFake();
    TEST_ASSERT_NOT_EQUAL(printFake, serialPrintFake);
}

static void test_getter_overload_with_mapping(void)
{
    Serial_* serial = &::Serial;
    Print* serialPrintFake = SimpleArduinoFake::getContext()._Serial.getFake(serial);

    TEST_ASSERT_EQUAL(SimpleArduinoFake::getContext()._Serial.getFake(), serialPrintFake);
    Print* printFake = SimpleArduinoFake::getContext()._Print.getFake();
    TEST_ASSERT_NOT_EQUAL(printFake, serialPrintFake);
}

namespace ArduinoContextTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_single_instance);
        RUN_TEST(test_function_mock);
        RUN_TEST(test_print_mock);
        RUN_TEST(test_stream_mock);
        RUN_TEST(test_serial_mock);
        RUN_TEST(test_getter_overload_with_proxy);
        RUN_TEST(test_getter_overload_with_mapping);
        RUN_TEST(test_unknown_instance_exception);

        test_reset();
    }
}

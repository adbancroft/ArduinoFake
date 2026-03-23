#include <Arduino.h>
#include <ArduinoFake.h>
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_single_instance(void)
{
    ArduinoFakeContext* context1 = &getArduinoFakeContext();
    ArduinoFakeContext* context2 = &getArduinoFakeContext();

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
    ArduinoFakeReset();
    
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
    auto method = Method(ArduinoFake(Function), millis);
    When(method).AlwaysReturn(101L);
    assert_test_reset(method, []() { (void)millis(); });
}

static void test_reset_print(void)
{
    auto method = OverloadedMethod(ArduinoFake(Print), print, size_t(const char[]));
    When(method).AlwaysDo([](const char *str) {
        std::cout << str;
        return strlen(str);
    });
    assert_test_reset(method, []() { (ArduinoFakeInstance(Print))->print("abc"); });
}

static void test_reset_serial(void)
{
    auto method = Method(ArduinoFake(Serial), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance(Serial))->end(); });
}

static void test_reset_wire(void)
{
    auto method = Method(ArduinoFake(Wire), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance(Wire))->end(); });
}

static void test_reset_stream(void)
{
    auto method = OverloadedMethod(ArduinoFake(Stream), find, bool(const char *));
    When(method).AlwaysReturn(false);
    assert_test_reset(method, []() { 
        char toFind[] = "abc";
        (ArduinoFakeInstance(Stream))->find(toFind); 
    });
}

static void test_reset_client(void)
{
    auto method = Method(ArduinoFake(Client), available);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { ArduinoFakeInstance(Client)->available(); });
}

static void test_reset_spi(void)
{
    auto method = Method(ArduinoFake(SPI), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance(SPI))->end(); });
}

static void test_reset_eeprom(void)
{
    auto method = Method(ArduinoFake(EEPROM), length);
    When(method).AlwaysReturn(0xffff);
    assert_test_reset(method, []() { (ArduinoFakeInstance(EEPROM))->length(); });
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
    Mock<ArduinoFake::details::FunctionFake>* m1 = &ArduinoFake(Function);
    Mock<ArduinoFake::details::FunctionFake>* m2 = &ArduinoFake(Function);
    Mock<ArduinoFake::details::FunctionFake>* m3 = &ArduinoFake();

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_NOT_NULL(m3);

    TEST_ASSERT_EQUAL(m1, m2);
    TEST_ASSERT_EQUAL(m1, m3);

    ArduinoFake::details::FunctionFake* i1 = ArduinoFakeInstance(Function);
    ArduinoFake::details::FunctionFake* i2 = ArduinoFakeInstance(Function);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_print_mock(void)
{
    Mock<Print>* m1 = &ArduinoFake(Print);
    Mock<Print>* m2 = &ArduinoFake(Print);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    Print* i1 = ArduinoFakeInstance(Print);
    Print* i2 = ArduinoFakeInstance(Print);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_stream_mock(void)
{
    Mock<Stream>* m1 = &ArduinoFake(Stream);
    Mock<Stream>* m2 = &ArduinoFake(Stream);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    Stream* i1 = ArduinoFakeInstance(Stream);
    Stream* i2 = ArduinoFakeInstance(Stream);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_serial_mock(void)
{
    Mock<Serial_>* m1 = &ArduinoFake(Serial);
    Mock<Serial_>* m2 = &ArduinoFake(Serial);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    Serial_* i1 = ArduinoFakeInstance(Serial);
    Serial_* i2 = ArduinoFakeInstance(Serial);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_unknown_instance_exception(void)
{
    fakeit::Mock<Serial_> fake;

    try {
        ArduinoFakeInstance(Serial, &fake.get());
    } catch (const std::runtime_error& e) {
        TEST_ASSERT_EQUAL_STRING("Unknown instance", e.what());
    }
}

static void test_getter_overload_with_proxy(void)
{
    Serial_* serial(ArduinoFakeInstance(Serial));
    Print* serialPrintFake = ArduinoFakeInstance(Serial, serial);

    TEST_ASSERT_EQUAL(ArduinoFakeInstance(Serial), serialPrintFake);
    Print* printFake = ArduinoFakeInstance(Print);
    TEST_ASSERT_NOT_EQUAL(printFake, serialPrintFake);
}

static void test_getter_overload_with_mapping(void)
{
    Serial_* serial = &::Serial;
    Print* serialPrintFake = ArduinoFakeInstance(Serial, serial);

    TEST_ASSERT_EQUAL(ArduinoFakeInstance(Serial), serialPrintFake);
    Print* printFake = ArduinoFakeInstance(Print);
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

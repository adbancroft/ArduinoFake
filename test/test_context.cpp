#include <Arduino.h>
#include <ArduinoFake.h>
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_single_instance(void)
{
    ArduinoFakeContext* context1 = getArduinoFakeContext();
    ArduinoFakeContext* context2 = getArduinoFakeContext();

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
    assert_test_reset(method, []() { (ArduinoFakeInstance0(Print))->print("abc"); });
}

static void test_reset_serial(void)
{
    auto method = Method(ArduinoFake(Serial), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance0(Serial))->end(); });
}

static void test_reset_wire(void)
{
    auto method = Method(ArduinoFake(Wire), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance0(Wire))->end(); });
}

static void test_reset_stream(void)
{
    auto method = OverloadedMethod(ArduinoFake(Stream), find, bool(const char *));
    When(method).AlwaysReturn(false);
    assert_test_reset(method, []() { 
        char toFind[] = "abc";
        (ArduinoFakeInstance0(Stream))->find(toFind); 
    });
}

static void test_reset_client(void)
{
    auto method = Method(ArduinoFake(Client), available);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { ArduinoFakeInstance0(Client)->available(); });
}

static void test_reset_spi(void)
{
    auto method = Method(ArduinoFake(SPI), end);
    When(method).AlwaysReturn();
    assert_test_reset(method, []() { (ArduinoFakeInstance0(SPI))->end(); });
}

static void test_reset_eeprom(void)
{
    auto method = Method(ArduinoFake(EEPROM), length);
    When(method).AlwaysReturn(0xffff);
    assert_test_reset(method, []() { (ArduinoFakeInstance0(EEPROM))->length(); });
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
    Mock<FunctionFake>* m1 = &ArduinoFake(Function);
    Mock<FunctionFake>* m2 = &ArduinoFake(Function);
    Mock<FunctionFake>* m3 = &ArduinoFake();

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_NOT_NULL(m3);

    TEST_ASSERT_EQUAL(m1, m2);
    TEST_ASSERT_EQUAL(m1, m3);

    FunctionFake* i1 = ArduinoFakeInstance0(Function);
    FunctionFake* i2 = ArduinoFakeInstance0(Function);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_print_mock(void)
{
    Mock<PrintFake>* m1 = &ArduinoFake(Print);
    Mock<PrintFake>* m2 = &ArduinoFake(Print);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    PrintFake* i1 = ArduinoFakeInstance0(Print);
    PrintFake* i2 = ArduinoFakeInstance0(Print);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_stream_mock(void)
{
    Mock<StreamFake>* m1 = &ArduinoFake(Stream);
    Mock<StreamFake>* m2 = &ArduinoFake(Stream);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    StreamFake* i1 = ArduinoFakeInstance0(Stream);
    StreamFake* i2 = ArduinoFakeInstance0(Stream);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_serial_mock(void)
{
    Mock<SerialFake>* m1 = &ArduinoFake(Serial);
    Mock<SerialFake>* m2 = &ArduinoFake(Serial);

    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
    TEST_ASSERT_EQUAL(m1, m2);

    SerialFake* i1 = ArduinoFakeInstance0(Serial);
    SerialFake* i2 = ArduinoFakeInstance0(Serial);

    TEST_ASSERT_NOT_NULL(i1);
    TEST_ASSERT_NOT_NULL(i2);
    TEST_ASSERT_EQUAL(i1, i2);
}

static void test_unknown_instance_exception(void)
{
    fakeit::Mock<Serial_> fake;

    try {
        ArduinoFakeInstance(&fake.get());
    } catch (const std::runtime_error& e) {
        TEST_ASSERT_EQUAL_STRING("Unknown instance", e.what());
    }
}

static void test_getter_overload_with_proxy(void)
{
    Serial_* serial(ArduinoFakeInstance0(Serial));
    PrintFake* serialPrintFake = ArduinoFakeInstance(serial);

    TEST_ASSERT_EQUAL(getArduinoFakeContext()->Serial(), serialPrintFake);
    PrintFake* printFake = ArduinoFakeInstance0(Print);
    TEST_ASSERT_NOT_EQUAL(printFake, serialPrintFake);
}

static void test_getter_overload_with_mapping(void)
{
    Serial_* serial = &::Serial;
    PrintFake* serialPrintFake = ArduinoFakeInstance(serial);

    TEST_ASSERT_EQUAL(getArduinoFakeContext()->Serial(), serialPrintFake);
    PrintFake* printFake = ArduinoFakeInstance0(Print);
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

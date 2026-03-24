#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_extends_stream(void)
{
    auto &serialFake = SimpleArduinoFake::getContext()._Serial;
    auto &streamFake = SimpleArduinoFake::getContext()._Stream;

    char print_char_var = 'A';
    char stream_char_var = 'B';

    int print_int_var = 123;
    int stream_int_var = 321;

    When(OverloadedMethod(streamFake, print, size_t(char))).AlwaysReturn();
    When(OverloadedMethod(streamFake, print, size_t(int, int))).AlwaysReturn();

    When(OverloadedMethod(serialFake, print, size_t(char))).AlwaysReturn();
    When(OverloadedMethod(serialFake, print, size_t(int, int))).AlwaysReturn();

    Stream* pStream(streamFake.getFake());
    Serial_* serial(serialFake.getFake());
    TEST_ASSERT_NOT_EQUAL(pStream, serial);

    pStream->print(stream_char_var);
    pStream->print(stream_int_var, DEC);

    serial->print(print_char_var);
    serial->print(print_int_var, DEC);

    Verify(OverloadedMethod(streamFake, print, size_t(char)).Using(stream_char_var)).Once();
    Verify(OverloadedMethod(streamFake, print, size_t(int, int)).Using(stream_int_var, DEC)).Once();

    Verify(OverloadedMethod(serialFake, print, size_t(char)).Using(print_char_var)).Once();
    Verify(OverloadedMethod(serialFake, print, size_t(int, int)).Using(print_int_var, DEC)).Once();
}

static void test_global_serial(void)
{
    auto &serialFake = SimpleArduinoFake::getContext()._Serial;
    When(Method(serialFake, available)).Return(1);
    When(OverloadedMethod(serialFake, print, size_t(char))).Return(1);

    TEST_ASSERT_EQUAL(1, Serial.available());
    TEST_ASSERT_EQUAL(1, Serial.print('A'));

    Verify(Method(serialFake, available)).Once();
    Verify(OverloadedMethod(serialFake, print, size_t(char)).Using('A')).Once();
}

static void test_basics(void)
{
    auto &serialFake = SimpleArduinoFake::getContext()._Serial;
    When(Method(serialFake, end)).AlwaysReturn();
    When(Method(serialFake, flush)).AlwaysReturn();
    When(Method(serialFake, available)).Return(0, 1);
    When(OverloadedMethod(serialFake, write, size_t(uint8_t))).Return(1);
    When(OverloadedMethod(serialFake, begin, void(unsigned long))).AlwaysReturn();

    Serial.begin(9600);

    TEST_ASSERT_EQUAL(0, Serial.available());
    TEST_ASSERT_EQUAL(1, Serial.available());
    TEST_ASSERT_EQUAL(1, Serial.write(5));

    Serial.flush();
    Serial.end();

    Verify(OverloadedMethod(serialFake, begin, void(unsigned long)).Using(9600)).Once();
    Verify(Method(serialFake, available)).Exactly(2_Times);

    Verify(OverloadedMethod(serialFake, write, size_t(uint8_t)).Using(5)).Once();

    Verify(Method(serialFake, flush)).Once();
    Verify(Method(serialFake, end)).Once();
}

namespace SerialTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_extends_stream);
        RUN_TEST(test_global_serial);
        RUN_TEST(test_basics);
    }
}

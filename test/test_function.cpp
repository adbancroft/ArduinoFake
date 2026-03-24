#include <Arduino.h>
#include <ArduinoFake.h>
#include <unity.h>
#include <stdint.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_init(void)
{
    When(Method(getArduinoFakeContext()._Function, init)).AlwaysReturn();

    init();

    Verify(Method(getArduinoFakeContext()._Function, init)).Once();
}

static void test_timestamps(void)
{
    When(Method(getArduinoFakeContext()._Function, micros)).AlwaysReturn(100000);
    When(Method(getArduinoFakeContext()._Function, millis)).AlwaysReturn(200000);

    TEST_ASSERT_EQUAL(100000, micros());
    TEST_ASSERT_EQUAL(200000, millis());

    Verify(Method(getArduinoFakeContext()._Function, micros)).Once();
    Verify(Method(getArduinoFakeContext()._Function, millis)).Once();
}

static void test_pin_mode(void)
{
    When(Method(getArduinoFakeContext()._Function, pinMode)).AlwaysReturn();

    pinMode(3, INPUT);
    Verify(Method(getArduinoFakeContext()._Function, pinMode).Using(3, INPUT)).Once();

    pinMode(3, OUTPUT);
    Verify(Method(getArduinoFakeContext()._Function, pinMode).Using(3, INPUT)).Once();
}

static void test_digital_pin(void)
{
    When(Method(getArduinoFakeContext()._Function, digitalWrite)).AlwaysReturn();
    When(Method(getArduinoFakeContext()._Function, digitalRead)).AlwaysReturn(LOW);

    digitalWrite(3, HIGH);
    Verify(Method(getArduinoFakeContext()._Function, digitalWrite).Using(3, HIGH)).Once();

    TEST_ASSERT_EQUAL(LOW, digitalRead(4));
    Verify(Method(getArduinoFakeContext()._Function, digitalRead).Using(4)).Once();
}

static void test_analog_pin(void)
{
    When(Method(getArduinoFakeContext()._Function, analogWrite)).AlwaysReturn();
    When(Method(getArduinoFakeContext()._Function, analogRead)).AlwaysReturn(123);

    analogWrite(3, 321);
    Verify(Method(getArduinoFakeContext()._Function, analogWrite).Using(3, 321)).Once();

    TEST_ASSERT_EQUAL(123, analogRead(4));
    Verify(Method(getArduinoFakeContext()._Function, analogRead).Using(4)).Once();
}

static void test_analog_read_resolution(void)
{
    When(Method(getArduinoFakeContext()._Function, analogReadResolution)).AlwaysReturn();

    analogReadResolution(12);

    Verify(Method(getArduinoFakeContext()._Function, analogReadResolution).Using(12)).Once();
}

static void test_yield(void)
{
    When(Method(getArduinoFakeContext()._Function, yield)).AlwaysReturn();

    yield();

    Verify(Method(getArduinoFakeContext()._Function, yield)).Once();
}

static void test_delay(void)
{
    When(Method(getArduinoFakeContext()._Function, delay)).AlwaysReturn();
    When(Method(getArduinoFakeContext()._Function, delayMicroseconds)).AlwaysReturn();

    delay(100);
    delayMicroseconds(200);

    Verify(Method(getArduinoFakeContext()._Function, delay).Using(100)).Once();
    Verify(Method(getArduinoFakeContext()._Function, delayMicroseconds).Using(200)).Once();
}

static void test_pulsein(void)
{
    When(Method(getArduinoFakeContext()._Function, pulseIn)).AlwaysReturn(1000);

    TEST_ASSERT_EQUAL(1000,  pulseIn(10, HIGH, 1234));

    Verify(Method(getArduinoFakeContext()._Function, pulseIn).Using(10, HIGH, 1234)).Once();
}

static void test_shift(void)
{
    When(Method(getArduinoFakeContext()._Function, shiftIn)).AlwaysReturn(8);
    When(Method(getArduinoFakeContext()._Function, shiftOut)).AlwaysReturn();

    shiftOut(10, 11, LSBFIRST, 8);
    Verify(Method(getArduinoFakeContext()._Function, shiftOut).Using(10, 11, LSBFIRST, 8)).Once();

    TEST_ASSERT_EQUAL(8, shiftIn(5, 6, MSBFIRST));
    Verify(Method(getArduinoFakeContext()._Function, shiftIn).Using(5, 6, MSBFIRST)).Once();
}

static void test_detach(void)
{
    When(Method(getArduinoFakeContext()._Function, detachInterrupt)).AlwaysReturn();

    detachInterrupt(1);

    Verify(Method(getArduinoFakeContext()._Function, detachInterrupt).Using(1)).Once();
}

static void test_attach(void)
{
    When(Method(getArduinoFakeContext()._Function, attachInterrupt)).AlwaysReturn();

    attachInterrupt(1, (void (*)(void))NULL, FALLING);
    attachInterrupt(2, (void (*)(void))NULL, CHANGE);
    attachInterrupt(3, (void (*)(void))NULL, RISING);

    Verify(Method(getArduinoFakeContext()._Function, attachInterrupt)).Exactly(3);
}

static void test_cli(void)
{
    When(Method(getArduinoFakeContext()._Function, cli)).AlwaysReturn();

    cli();

    Verify(Method(getArduinoFakeContext()._Function, cli)).Once();
}

static void test_sei(void)
{
    When(Method(getArduinoFakeContext()._Function, sei)).AlwaysReturn();

    sei();

    Verify(Method(getArduinoFakeContext()._Function, sei)).Once();
}

static void test_random(void)
{
    When(Method(getArduinoFakeContext()._Function, randomSeed)).AlwaysReturn();
    When(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long))).Return(10, 11);
    When(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long, long))).Return(20, 21);

    randomSeed(123);

    TEST_ASSERT_EQUAL(10,  random(10));
    TEST_ASSERT_EQUAL(11,  random(15));
    TEST_ASSERT_EQUAL(20,  random(5, 20));
    TEST_ASSERT_EQUAL(21,  random(10, 25));

    Verify(Method(getArduinoFakeContext()._Function, randomSeed).Using(123)).Once();

    Verify(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long)).Using(10)).Once();
    Verify(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long)).Using(15)).Once();

    Verify(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long, long)).Using(5, 20)).Once();
    Verify(OverloadedMethod(getArduinoFakeContext()._Function, random, long(long, long)).Using(10, 25)).Once();
}

static void test_tone(void)
{
    When(Method(getArduinoFakeContext()._Function, tone)).AlwaysReturn();
    When(Method(getArduinoFakeContext()._Function, noTone)).AlwaysReturn();

    tone(7, 1047, 8);
    tone(8, 1319, 4);
    tone(9, 1568, 2);

    noTone(7);
    noTone(8);
    noTone(9);

    Verify(Method(getArduinoFakeContext()._Function, tone).Using(7, 1047, 8)).Once();
    Verify(Method(getArduinoFakeContext()._Function, tone).Using(8, 1319, 4)).Once();
    Verify(Method(getArduinoFakeContext()._Function, tone).Using(9, 1568, 2)).Once();

    Verify(Method(getArduinoFakeContext()._Function, noTone).Using(7)).Once();
    Verify(Method(getArduinoFakeContext()._Function, noTone).Using(8)).Once();
    Verify(Method(getArduinoFakeContext()._Function, noTone).Using(9)).Once();
}

static void test_map(void)
{
    When(Method(getArduinoFakeContext()._Function, map)).Return(5);

    TEST_ASSERT_EQUAL(5, map(50, 0, 100, 0, 10));

    Verify(Method(getArduinoFakeContext()._Function, map).Using(50, 0, 100, 0, 10)).Once();
}

static void test_digitalPinToPort(void)
{
    When(Method(getArduinoFakeContext()._Function, digitalPinToPort)).Return(5);

    TEST_ASSERT_EQUAL(5, digitalPinToPort(50));

    Verify(Method(getArduinoFakeContext()._Function, digitalPinToPort)).Once();
}

static void test_digitalPinToBitMask(void)
{
    When(Method(getArduinoFakeContext()._Function, digitalPinToBitMask)).Return(5);

    TEST_ASSERT_EQUAL(5, digitalPinToBitMask(50));

    Verify(Method(getArduinoFakeContext()._Function, digitalPinToBitMask)).Once();
}

static void test_digitalPinToTimer(void)
{
    When(Method(getArduinoFakeContext()._Function, digitalPinToTimer)).Return(5);

    TEST_ASSERT_EQUAL(5, digitalPinToTimer(50));

    Verify(Method(getArduinoFakeContext()._Function, digitalPinToTimer)).Once();
}

static void test_portOutputRegister(void)
{
    volatile uint8_t expected = 5;
    When(Method(getArduinoFakeContext()._Function, portOutputRegister)).Return(&expected);

    TEST_ASSERT_EQUAL(5, *portOutputRegister(50));

    Verify(Method(getArduinoFakeContext()._Function, portOutputRegister)).Once();
}

static void test_portInputRegister(void)
{
    volatile uint8_t expected = 5;
    When(Method(getArduinoFakeContext()._Function, portInputRegister)).Return(&expected);

    TEST_ASSERT_EQUAL(5, *portInputRegister(50));

    Verify(Method(getArduinoFakeContext()._Function, portInputRegister)).Once();
}

static void test_portModeRegister(void)
{
    volatile uint8_t expected = 5;
    When(Method(getArduinoFakeContext()._Function, portModeRegister)).Return(&expected);

    TEST_ASSERT_EQUAL(5, *portModeRegister(50));

    Verify(Method(getArduinoFakeContext()._Function, portModeRegister)).Once();
}

namespace FunctionTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_init);
        RUN_TEST(test_timestamps);
        RUN_TEST(test_pin_mode);
        RUN_TEST(test_digital_pin);
        RUN_TEST(test_analog_pin);
        RUN_TEST(test_analog_read_resolution);
        RUN_TEST(test_delay);
        RUN_TEST(test_detach);
        RUN_TEST(test_attach);
        RUN_TEST(test_cli);        
        RUN_TEST(test_sei);
        RUN_TEST(test_pulsein);
        RUN_TEST(test_shift);
        RUN_TEST(test_random);
        RUN_TEST(test_tone);
        RUN_TEST(test_map);
        RUN_TEST(test_digitalPinToPort);
        RUN_TEST(test_digitalPinToBitMask);
        RUN_TEST(test_digitalPinToTimer);
        RUN_TEST(test_portOutputRegister);
        RUN_TEST(test_portInputRegister);
        RUN_TEST(test_portModeRegister);
    }
}

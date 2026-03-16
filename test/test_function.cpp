#include <Arduino.h>
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_init(void)
{
    When(Method(ArduinoFake(), init)).AlwaysReturn();

    init();

    Verify(Method(ArduinoFake(), init)).Once();
}

static void test_timestamps(void)
{
    When(Method(ArduinoFake(), micros)).AlwaysReturn(100000);
    When(Method(ArduinoFake(), millis)).AlwaysReturn(200000);

    TEST_ASSERT_EQUAL(100000, micros());
    TEST_ASSERT_EQUAL(200000, millis());

    Verify(Method(ArduinoFake(), micros)).Once();
    Verify(Method(ArduinoFake(), millis)).Once();
}

static void test_pin_mode(void)
{
    When(Method(ArduinoFake(), pinMode)).AlwaysReturn();

    pinMode(3, INPUT);
    Verify(Method(ArduinoFake(), pinMode).Using(3, INPUT)).Once();

    pinMode(3, OUTPUT);
    Verify(Method(ArduinoFake(), pinMode).Using(3, INPUT)).Once();
}

static void test_digital_pin(void)
{
    When(Method(ArduinoFake(), digitalWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), digitalRead)).AlwaysReturn(LOW);

    digitalWrite(3, HIGH);
    Verify(Method(ArduinoFake(), digitalWrite).Using(3, HIGH)).Once();

    TEST_ASSERT_EQUAL(LOW, digitalRead(4));
    Verify(Method(ArduinoFake(), digitalRead).Using(4)).Once();
}

static void test_analog_pin(void)
{
    When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    When(Method(ArduinoFake(), analogRead)).AlwaysReturn(123);

    analogWrite(3, 321);
    Verify(Method(ArduinoFake(), analogWrite).Using(3, 321)).Once();

    TEST_ASSERT_EQUAL(123, analogRead(4));
    Verify(Method(ArduinoFake(), analogRead).Using(4)).Once();
}

static void test_analog_read_resolution(void)
{
    When(Method(ArduinoFake(), analogReadResolution)).AlwaysReturn();

    analogReadResolution(12);

    Verify(Method(ArduinoFake(), analogReadResolution).Using(12)).Once();
}

static void test_yield(void)
{
    When(Method(ArduinoFake(), yield)).AlwaysReturn();

    yield();

    Verify(Method(ArduinoFake(), yield)).Once();
}

static void test_delay(void)
{
    When(Method(ArduinoFake(), delay)).AlwaysReturn();
    When(Method(ArduinoFake(), delayMicroseconds)).AlwaysReturn();

    delay(100);
    delayMicroseconds(200);

    Verify(Method(ArduinoFake(), delay).Using(100)).Once();
    Verify(Method(ArduinoFake(), delayMicroseconds).Using(200)).Once();
}

static void test_pulsein(void)
{
    When(Method(ArduinoFake(), pulseIn)).AlwaysReturn(1000);

    TEST_ASSERT_EQUAL(1000,  pulseIn(10, HIGH, 1234));

    Verify(Method(ArduinoFake(), pulseIn).Using(10, HIGH, 1234)).Once();
}

static void test_shift(void)
{
    When(Method(ArduinoFake(), shiftIn)).AlwaysReturn(8);
    When(Method(ArduinoFake(), shiftOut)).AlwaysReturn();

    shiftOut(10, 11, LSBFIRST, 8);
    Verify(Method(ArduinoFake(), shiftOut).Using(10, 11, LSBFIRST, 8)).Once();

    TEST_ASSERT_EQUAL(8, shiftIn(5, 6, MSBFIRST));
    Verify(Method(ArduinoFake(), shiftIn).Using(5, 6, MSBFIRST)).Once();
}

static void test_detach(void)
{
    When(Method(ArduinoFake(), detachInterrupt)).AlwaysReturn();

    detachInterrupt(1);

    Verify(Method(ArduinoFake(), detachInterrupt).Using(1)).Once();
}

static void test_attach(void)
{
    When(Method(ArduinoFake(), attachInterrupt)).AlwaysReturn();

    attachInterrupt(1, (void (*)(void))NULL, FALLING);
    attachInterrupt(2, (void (*)(void))NULL, CHANGE);
    attachInterrupt(3, (void (*)(void))NULL, RISING);

    Verify(Method(ArduinoFake(), attachInterrupt)).Exactly(3);
}

static void test_cli(void)
{
    When(Method(ArduinoFake(), cli)).AlwaysReturn();

    cli();

    Verify(Method(ArduinoFake(), cli)).Once();
}

static void test_sei(void)
{
    When(Method(ArduinoFake(), sei)).AlwaysReturn();

    sei();

    Verify(Method(ArduinoFake(), sei)).Once();
}

static void test_random(void)
{
    When(Method(ArduinoFake(), randomSeed)).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake(), random, long(long))).Return(10, 11);
    When(OverloadedMethod(ArduinoFake(), random, long(long, long))).Return(20, 21);

    randomSeed(123);

    TEST_ASSERT_EQUAL(10,  random(10));
    TEST_ASSERT_EQUAL(11,  random(15));
    TEST_ASSERT_EQUAL(20,  random(5, 20));
    TEST_ASSERT_EQUAL(21,  random(10, 25));

    Verify(Method(ArduinoFake(), randomSeed).Using(123)).Once();

    Verify(OverloadedMethod(ArduinoFake(), random, long(long)).Using(10)).Once();
    Verify(OverloadedMethod(ArduinoFake(), random, long(long)).Using(15)).Once();

    Verify(OverloadedMethod(ArduinoFake(), random, long(long, long)).Using(5, 20)).Once();
    Verify(OverloadedMethod(ArduinoFake(), random, long(long, long)).Using(10, 25)).Once();
}

static void test_tone(void)
{
    When(Method(ArduinoFake(), tone)).AlwaysReturn();
    When(Method(ArduinoFake(), noTone)).AlwaysReturn();

    tone(7, 1047, 8);
    tone(8, 1319, 4);
    tone(9, 1568, 2);

    noTone(7);
    noTone(8);
    noTone(9);

    Verify(Method(ArduinoFake(), tone).Using(7, 1047, 8)).Once();
    Verify(Method(ArduinoFake(), tone).Using(8, 1319, 4)).Once();
    Verify(Method(ArduinoFake(), tone).Using(9, 1568, 2)).Once();

    Verify(Method(ArduinoFake(), noTone).Using(7)).Once();
    Verify(Method(ArduinoFake(), noTone).Using(8)).Once();
    Verify(Method(ArduinoFake(), noTone).Using(9)).Once();
}

static void test_map(void)
{
    When(Method(ArduinoFake(), map)).Return(5);

    TEST_ASSERT_EQUAL(5, map(50, 0, 100, 0, 10));

    Verify(Method(ArduinoFake(), map).Using(50, 0, 100, 0, 10)).Once();
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
    }
}

#include <Arduino.h>
#include <ArduinoFake.h>
#include <unity.h>
#include "arduino/EEPROM.h"
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_basics(void) {
  When(OverloadedMethod(ArduinoFake::getContext()._EEPROM, read, uint8_t(int)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake::getContext()._EEPROM, write, void(int, uint8_t)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake::getContext()._EEPROM, update, void(int, uint8_t)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake::getContext()._EEPROM, length, uint16_t(void)))
      .AlwaysReturn();

  EEPROM.read(1);
  EEPROM.write(1, 1);
  EEPROM.update(1, 2);
  EEPROM.length();

  Verify(OverloadedMethod(ArduinoFake::getContext()._EEPROM, read, uint8_t(int))).Once();
  Verify(OverloadedMethod(ArduinoFake::getContext()._EEPROM, write, void(int, uint8_t)))
      .Once();
  Verify(OverloadedMethod(ArduinoFake::getContext()._EEPROM, update, void(int, uint8_t)))
      .Once();
  Verify(OverloadedMethod(ArduinoFake::getContext()._EEPROM, length, uint16_t(void))).Once();
}

static void test_get(void) {
    When(Method(ArduinoFake::getContext()._EEPROM, read)).AlwaysReturn((uint8_t)INT8_MAX);

    uint16_t arr[] = { UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX, UINT16_MAX };
    EEPROM.get(0, arr);

    Verify(Method(ArduinoFake::getContext()._EEPROM, read)).Exactly(sizeof(arr));

    constexpr uint16_t expected = INT8_MAX | (INT8_MAX << 8U);
    TEST_ASSERT_EQUAL(expected, arr[0]);
    TEST_ASSERT_EQUAL(expected, arr[1]);
    TEST_ASSERT_EQUAL(expected, arr[2]);
    TEST_ASSERT_EQUAL(expected, arr[3]);
    TEST_ASSERT_EQUAL(expected, arr[4]);
}

static void test_put(void) {
    When(Method(ArduinoFake::getContext()._EEPROM, update)).AlwaysReturn();

    const int16_t arr[] = { INT16_MAX, INT16_MIN };
    constexpr int idx = 101;
    EEPROM.put(idx, arr);

    const uint8_t *pSource = (const uint8_t *)arr;
    for (int i = 0; i < sizeof(arr); ++i) {
        Verify(Method(ArduinoFake::getContext()._EEPROM, update).Using(idx + i, pSource[i])).Once();
    }
}

namespace EEPROMTest {
    void run_tests(void) { 
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_basics); 
        RUN_TEST(test_get);
        RUN_TEST(test_put);
    } 

} // namespace EEPROMTest

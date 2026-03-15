#include <Arduino.h>
#include <unity.h>
#include "arduino/EEPROM.h"

using namespace fakeit;

static void test_basics(void) {
  When(OverloadedMethod(ArduinoFake(EEPROM), read, uint8_t(int)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(EEPROM), write, void(int, uint8_t)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(EEPROM), update, void(int, uint8_t)))
      .AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(EEPROM), length, uint16_t(void)))
      .AlwaysReturn();

  EEPROM.read(1);
  EEPROM.write(1, 1);
  EEPROM.update(1, 2);
  EEPROM.length();

  Verify(OverloadedMethod(ArduinoFake(EEPROM), read, uint8_t(int))).Once();
  Verify(OverloadedMethod(ArduinoFake(EEPROM), write, void(int, uint8_t)))
      .Once();
  Verify(OverloadedMethod(ArduinoFake(EEPROM), update, void(int, uint8_t)))
      .Once();
  Verify(OverloadedMethod(ArduinoFake(EEPROM), length, uint16_t(void))).Once();
}

namespace EEPROMTest {
    void run_tests(void) { 
        RUN_TEST(test_basics); 
    }
} 

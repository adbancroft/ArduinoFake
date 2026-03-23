// clang-format off
#include "ArduinoFake.h"
// clang-format on

uint8_t EEPROMClass::read(int idx) {
  return ArduinoFakeInstance(this)->read(idx);
};
void EEPROMClass::write(int idx, uint8_t val) {
  ArduinoFakeInstance(this)->write(idx, val);
};
void EEPROMClass::update(int idx, uint8_t val) {
  ArduinoFakeInstance(this)->update(idx, val);
};
uint16_t EEPROMClass::length() { return ArduinoFakeInstance(this)->length(); }

EEPROMClass EEPROM;

// clang-format off
#include "ArduinoFake.h"
// clang-format on

uint8_t EEPROMClass::read(int idx) {
  return ArduinoFake::getContext()._EEPROM.getFake(this)->read(idx);
};
void EEPROMClass::write(int idx, uint8_t val) {
  ArduinoFake::getContext()._EEPROM.getFake(this)->write(idx, val);
};
void EEPROMClass::update(int idx, uint8_t val) {
  ArduinoFake::getContext()._EEPROM.getFake(this)->update(idx, val);
};
uint16_t EEPROMClass::length() { return ArduinoFake::getContext()._EEPROM.getFake(this)->length(); }

EEPROMClass EEPROM;

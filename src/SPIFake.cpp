#include "ArduinoFake.h"

void SPIClass::begin() { ArduinoFakeInstance(this)->begin(); };

void SPIClass::end() { ArduinoFakeInstance(this)->end(); };

void SPIClass::beginTransaction(SPISettings settings) {
  ArduinoFakeInstance(this)->beginTransaction(settings);
};

void SPIClass::endTransaction(void) {
  ArduinoFakeInstance(this)->endTransaction();
};

uint8_t SPIClass::transfer(uint8_t data) {
  return ArduinoFakeInstance(this)->transfer(data);
};

uint16_t SPIClass::transfer16(uint16_t data) {
  return ArduinoFakeInstance(this)->transfer16(data);
};

void SPIClass::transfer(void *buf, size_t count) {
  return ArduinoFakeInstance(this)->transfer(buf, count);
};

SPIClass SPI;

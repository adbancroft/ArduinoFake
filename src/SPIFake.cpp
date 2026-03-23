#include "ArduinoFake.h"

void SPIClass::begin() { ArduinoFakeInstance(SPI, this)->begin(); };

void SPIClass::end() { ArduinoFakeInstance(SPI, this)->end(); };

void SPIClass::beginTransaction(SPISettings settings) {
  ArduinoFakeInstance(SPI, this)->beginTransaction(settings);
};

void SPIClass::endTransaction(void) {
  ArduinoFakeInstance(SPI, this)->endTransaction();
};

uint8_t SPIClass::transfer(uint8_t data) {
  return ArduinoFakeInstance(SPI, this)->transfer(data);
};

uint16_t SPIClass::transfer16(uint16_t data) {
  return ArduinoFakeInstance(SPI, this)->transfer16(data);
};

void SPIClass::transfer(void *buf, size_t count) {
  return ArduinoFakeInstance(SPI, this)->transfer(buf, count);
};

SPIClass SPI;

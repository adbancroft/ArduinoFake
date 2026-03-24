#include "ArduinoFake.h"

void SPIClass::begin() { ArduinoFake::getContext()._SPI.getFake(this)->begin(); };

void SPIClass::end() { ArduinoFake::getContext()._SPI.getFake(this)->end(); };

void SPIClass::beginTransaction(SPISettings settings) {
  ArduinoFake::getContext()._SPI.getFake(this)->beginTransaction(settings);
};

void SPIClass::endTransaction(void) {
  ArduinoFake::getContext()._SPI.getFake(this)->endTransaction();
};

uint8_t SPIClass::transfer(uint8_t data) {
  return ArduinoFake::getContext()._SPI.getFake(this)->transfer(data);
};

uint16_t SPIClass::transfer16(uint16_t data) {
  return ArduinoFake::getContext()._SPI.getFake(this)->transfer16(data);
};

void SPIClass::transfer(void *buf, size_t count) {
  return ArduinoFake::getContext()._SPI.getFake(this)->transfer(buf, count);
};

SPIClass SPI;

#include "SimpleArduinoFake.h"

void SPIClass::begin() { SimpleArduinoFake::getContext()._SPI.getFake(this)->begin(); };

void SPIClass::end() { SimpleArduinoFake::getContext()._SPI.getFake(this)->end(); };

void SPIClass::beginTransaction(SPISettings settings) {
  SimpleArduinoFake::getContext()._SPI.getFake(this)->beginTransaction(settings);
};

void SPIClass::endTransaction(void) {
  SimpleArduinoFake::getContext()._SPI.getFake(this)->endTransaction();
};

uint8_t SPIClass::transfer(uint8_t data) {
  return SimpleArduinoFake::getContext()._SPI.getFake(this)->transfer(data);
};

uint16_t SPIClass::transfer16(uint16_t data) {
  return SimpleArduinoFake::getContext()._SPI.getFake(this)->transfer16(data);
};

void SPIClass::transfer(void *buf, size_t count) {
  return SimpleArduinoFake::getContext()._SPI.getFake(this)->transfer(buf, count);
};

SPIClass SPI;

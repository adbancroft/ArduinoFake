#include "ArduinoFake.h"

void TwoWire::begin(void) { ArduinoFake::getContext()._Wire.getFake(this)->begin(); }

void TwoWire::begin(uint8_t address) {

  ArduinoFake::getContext()._Wire.getFake(this)->begin(address);
}

void TwoWire::begin(int address) {
  ArduinoFake::getContext()._Wire.getFake(this)->begin(address);
}

void TwoWire::end(void) { ArduinoFake::getContext()._Wire.getFake(this)->end(); }

void TwoWire::setClock(uint32_t clock) {
  ArduinoFake::getContext()._Wire.getFake(this)->setClock(clock);
}

void TwoWire::setWireTimeout(uint32_t timeout, bool reset_with_timeout) {
  ArduinoFake::getContext()._Wire.getFake(this)->setWireTimeout(timeout, reset_with_timeout);
}

bool TwoWire::getWireTimeoutFlag(void) {
  return ArduinoFake::getContext()._Wire.getFake(this)->getWireTimeoutFlag();
}

void TwoWire::clearWireTimeoutFlag(void) {
  ArduinoFake::getContext()._Wire.getFake(this)->clearWireTimeoutFlag();
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint32_t iaddress, uint8_t isize,
                             uint8_t sendStop) {
  return ArduinoFake::getContext()._Wire.getFake(this)->requestFrom(address, quantity, iaddress, isize, sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint8_t sendStop) {
  return ArduinoFake::getContext()._Wire.getFake(this)->requestFrom(address, quantity, sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
  return ArduinoFake::getContext()._Wire.getFake(this)->requestFrom(address, quantity);
}

void TwoWire::beginTransmission(uint8_t address) {
  ArduinoFake::getContext()._Wire.getFake(this)->beginTransmission(address);
}

void TwoWire::beginTransmission(int address) {
  ArduinoFake::getContext()._Wire.getFake(this)->beginTransmission(address);
}

uint8_t TwoWire::endTransmission(bool sendStop) {

  return ArduinoFake::getContext()._Wire.getFake(this)->endTransmission(sendStop);
}

uint8_t TwoWire::endTransmission(void) {
  return ArduinoFake::getContext()._Wire.getFake(this)->endTransmission();
}

size_t TwoWire::write(uint8_t data) {
  return ArduinoFake::getContext()._Wire.getFake(this)->write(data);
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
  return ArduinoFake::getContext()._Wire.getFake(this)->write(data, quantity);
}

int TwoWire::available(void) {
  return ArduinoFake::getContext()._Wire.getFake(this)->available();
}

int TwoWire::read(void) { return ArduinoFake::getContext()._Wire.getFake(this)->read(); }

int TwoWire::peek(void) { return ArduinoFake::getContext()._Wire.getFake(this)->peek(); }

void TwoWire::flush(void) { ArduinoFake::getContext()._Wire.getFake(this)->flush(); }

void TwoWire::onReceive(void (*function)(int)) {
  ArduinoFake::getContext()._Wire.getFake(this)->onReceive(function);
}

void TwoWire::onRequest(void (*function)(void)) {
  ArduinoFake::getContext()._Wire.getFake(this)->onRequest(function);
}

TwoWire Wire;
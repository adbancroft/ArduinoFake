#include "ArduinoFake.h"
#include "WireFake.h"

void TwoWire::begin(void) { ArduinoFakeInstance(this)->begin(); }

void TwoWire::begin(uint8_t address) {

  ArduinoFakeInstance(this)->begin(address);
}

void TwoWire::begin(int address) {
  ArduinoFakeInstance(this)->begin(address);
}

void TwoWire::end(void) { ArduinoFakeInstance(this)->end(); }

void TwoWire::setClock(uint32_t clock) {
  ArduinoFakeInstance(this)->setClock(clock);
}

void TwoWire::setWireTimeout(uint32_t timeout, bool reset_with_timeout) {
  ArduinoFakeInstance(this)->setWireTimeout(timeout, reset_with_timeout);
}

bool TwoWire::getWireTimeoutFlag(void) {
  return ArduinoFakeInstance(this)->getWireTimeoutFlag();
}

void TwoWire::clearWireTimeoutFlag(void) {
  ArduinoFakeInstance(this)->clearWireTimeoutFlag();
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint32_t iaddress, uint8_t isize,
                             uint8_t sendStop) {
  return ArduinoFakeInstance(this)->requestFrom(address, quantity, iaddress, isize, sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity,
                             uint8_t sendStop) {
  return ArduinoFakeInstance(this)->requestFrom(address, quantity, sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity) {
  return ArduinoFakeInstance(this)->requestFrom(address, quantity);
}

void TwoWire::beginTransmission(uint8_t address) {
  ArduinoFakeInstance(this)->beginTransmission(address);
}

void TwoWire::beginTransmission(int address) {
  ArduinoFakeInstance(this)->beginTransmission(address);
}

uint8_t TwoWire::endTransmission(bool sendStop) {

  return ArduinoFakeInstance(this)->endTransmission(sendStop);
}

uint8_t TwoWire::endTransmission(void) {
  return ArduinoFakeInstance(this)->endTransmission();
}

size_t TwoWire::write(uint8_t data) {
  return ArduinoFakeInstance(this)->write(data);
}

size_t TwoWire::write(const uint8_t *data, size_t quantity) {
  return ArduinoFakeInstance(this)->write(data, quantity);
}

int TwoWire::available(void) {
  return ArduinoFakeInstance(this)->available();
}

int TwoWire::read(void) { return ArduinoFakeInstance(this)->read(); }

int TwoWire::peek(void) { return ArduinoFakeInstance(this)->peek(); }

void TwoWire::flush(void) { ArduinoFakeInstance(this)->flush(); }

void TwoWire::onReceive(void (*function)(int)) {
  ArduinoFakeInstance(this)->onReceive(function);
}

void TwoWire::onRequest(void (*function)(void)) {
  ArduinoFakeInstance(this)->onRequest(function);
}

TwoWire Wire = WireFakeProxy(ArduinoFakeInstance0(Wire));
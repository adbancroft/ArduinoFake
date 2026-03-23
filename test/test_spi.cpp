#include <Arduino.h>
#include <ArduinoFake.h>
#include <unity.h>
#include "arduino/SPI.h"
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_basics(void) {
  SPISettings settings(4000000, MSBFIRST, SPI_MODE0);
  uint8_t data = 0x01;
  uint16_t data16 = 0x1234;
  uint8_t buffer[] = {0x02, 0x03, 0x04};
  uint8_t *ptr = buffer;

  When(OverloadedMethod(ArduinoFake(SPI), begin, void(void))).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), end, void(void))).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), beginTransaction, void(SPISettings)).Using(settings)).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), endTransaction, void(void))).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), transfer, uint8_t(uint8_t)).Using(data)).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), transfer16, uint16_t(uint16_t)).Using(data16)).AlwaysReturn();
  When(OverloadedMethod(ArduinoFake(SPI), transfer, void(void*, size_t)).Using(ptr, sizeof(buffer))).AlwaysReturn();

  SPI.begin();
  SPI.beginTransaction(settings);
  SPI.transfer(data);
  SPI.transfer16(data16);
  SPI.transfer(buffer, sizeof(buffer));
  SPI.endTransaction();
  SPI.end();

  Verify(OverloadedMethod(ArduinoFake(SPI), begin, void(void))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), end, void(void))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), beginTransaction, void(SPISettings))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), endTransaction, void(void))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), transfer, uint8_t(uint8_t))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), transfer16, uint16_t(uint16_t))).Once();
  Verify(OverloadedMethod(ArduinoFake(SPI), transfer, void(void*, size_t))).Once();
}

namespace SpiTest {
  void run_tests(void) 
  { 
    unity_filename_helper_t _ufname_helper(__FILE__);
    RUN_TEST(test_basics);
  }
}
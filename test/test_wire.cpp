#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_extends_stream(void) {
  auto &streamFake = SimpleArduinoFake::getContext()._Stream;
  auto &wireFake = SimpleArduinoFake::getContext()._Wire;

  char print_char_var = 'A';
  char stream_char_var = 'B';

  int print_int_var = 123;
  int stream_int_var = 321;

  When(OverloadedMethod(streamFake, print, size_t(char))).AlwaysReturn();
  When(OverloadedMethod(streamFake, print, size_t(int, int))).AlwaysReturn();

  When(OverloadedMethod(wireFake, print, size_t(char))).AlwaysReturn();
  When(OverloadedMethod(wireFake, print, size_t(int, int))).AlwaysReturn();

  Stream* stream(streamFake.getFake());
  TwoWire* wire(wireFake.getFake());
  TEST_ASSERT_NOT_EQUAL(stream, wire);

  stream->print(stream_char_var);
  stream->print(stream_int_var, DEC);

  wire->print(print_char_var);
  wire->print(print_int_var, DEC);

  Verify(OverloadedMethod(streamFake, print, size_t(char)).Using(stream_char_var)).Once();
  Verify(OverloadedMethod(streamFake, print, size_t(int, int)).Using(stream_int_var, DEC)).Once();

  Verify(OverloadedMethod(wireFake, print, size_t(char)).Using(print_char_var)).Once();
  Verify(OverloadedMethod(wireFake, print, size_t(int, int)).Using(print_int_var, DEC)).Once();
}

static void test_global_wire(void) {
  auto &wireFake = SimpleArduinoFake::getContext()._Wire;
  When(Method(wireFake, available)).Return(1);
  When(OverloadedMethod(wireFake, print, size_t(char))).Return(1);

  TEST_ASSERT_EQUAL(1, Wire.available());
  TEST_ASSERT_EQUAL(1, Wire.print('A'));

  Verify(Method(wireFake, available)).Once();
  Verify(OverloadedMethod(wireFake, print, size_t(char)).Using('A')).Once();
}

static void test_basics(void) {

  uint8_t device_addr = 0xab;
  uint8_t register_addr = 0xcd;
  int num_bytes_to_read = 1;
  bool send_stop = false;

  auto &wireFake = SimpleArduinoFake::getContext()._Wire;
  When(OverloadedMethod(wireFake, begin, void(void))).AlwaysReturn();
  When(OverloadedMethod(wireFake, beginTransmission, void(uint8_t))).AlwaysReturn();
  When(OverloadedMethod(wireFake, write, size_t(uint8_t))).Return(true);
  When(OverloadedMethod(wireFake, endTransmission, uint8_t(bool))).Return(0);
  When(OverloadedMethod(wireFake, requestFrom, uint8_t(uint8_t, uint8_t))).Return(0);
  When(OverloadedMethod(wireFake, available, int(void))).Return(1);
  When(OverloadedMethod(wireFake, read, int(void))).Return(1);

  Wire.begin();
  Wire.beginTransmission(device_addr);
  Wire.write(register_addr);
  Wire.endTransmission(send_stop);
  Wire.requestFrom(device_addr, num_bytes_to_read);
  if (Wire.available()) {
    Wire.read();
  }

  Verify(OverloadedMethod(wireFake, begin, void(void))).Exactly(1);
  Verify(OverloadedMethod(wireFake, beginTransmission, void(uint8_t)).Using(device_addr)).Exactly(1);
  Verify(OverloadedMethod(wireFake, write, size_t(uint8_t)).Using(register_addr)).Exactly(1);
  Verify(OverloadedMethod(wireFake, endTransmission, uint8_t(bool)).Using(send_stop)).Exactly(1);
  Verify(OverloadedMethod(wireFake, requestFrom, uint8_t(uint8_t, uint8_t)).Using(device_addr, num_bytes_to_read)).Exactly(1);
  Verify(OverloadedMethod(wireFake, available, int(void))).Exactly(1);
  Verify(OverloadedMethod(wireFake, read, int(void))).Exactly(1);
}

namespace WireTest {
    void run_tests(void) {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_extends_stream);
        RUN_TEST(test_global_wire);
        RUN_TEST(test_basics);
    }
}
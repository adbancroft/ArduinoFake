#ifndef TwoWire_h
#define TwoWire_h

#include "Stream.h"
#include <inttypes.h>

class TwoWire : public Stream {
public:
  virtual void begin();
  virtual void begin(uint8_t);
  virtual void begin(int);
  virtual void end();
  virtual void setClock(uint32_t);
  virtual void setWireTimeout(uint32_t timeout = 25000,
                      bool reset_with_timeout = false);
  virtual bool getWireTimeoutFlag(void);
  virtual void clearWireTimeoutFlag(void);
  virtual void beginTransmission(uint8_t);
  virtual void beginTransmission(int);
  virtual uint8_t endTransmission(void);
  virtual uint8_t endTransmission(bool);
  virtual uint8_t requestFrom(uint8_t, uint8_t);
  virtual uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
  virtual uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *, size_t);
  virtual int available(void);
  virtual int read(void);
  virtual int peek(void);
  virtual void flush(void);
  virtual void onReceive(void (*)(int));
  virtual void onRequest(void (*)(void));

  inline size_t write(unsigned long n) { return write((uint8_t)n); }
  inline size_t write(long n) { return write((uint8_t)n); }
  inline size_t write(unsigned int n) { return write((uint8_t)n); }
  inline size_t write(int n) { return write((uint8_t)n); }
  using Print::write;
};

extern TwoWire Wire;

#endif

#pragma once
#include <inttypes.h>

struct EEPROMClass {
  virtual uint8_t read(int idx);
  virtual void write(int idx, uint8_t val);
  virtual void update(int idx, uint8_t val);
  virtual uint16_t length();
  /*
  EERef operator[](const int idx);
   */
  template< typename T > T &get( int idx, T &t ){
      unsigned char *ptr = (unsigned char*) &t;
      for( int count = sizeof(T) ; count ; --count, ++idx )
      {
        *ptr++ = read( idx );
      }
      return t;
  }
 
  template< typename T > const T &put( int idx, const T &t ){
      const unsigned char *ptr = (const unsigned char*) &t;
      for( int count = sizeof(T) ; count ; --count, ++idx )
      {
        update( idx, *ptr++ );
      }
      return t;
  }
 };

extern EEPROMClass EEPROM;
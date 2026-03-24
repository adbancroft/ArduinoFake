#include "ArduinoFake.h"

#if defined(USBCON)

void Serial_::begin(unsigned long baud_count)
{
    ArduinoFake::getContext()._Serial.getFake(this)->begin(baud_count);
}

void Serial_::begin(unsigned long baud_count, byte config)
{
    ArduinoFake::getContext()._Serial.getFake(this)->begin(baud_count, config);
}

void Serial_::end(void)
{
    ArduinoFake::getContext()._Serial.getFake(this)->end();
}

int Serial_::available(void)
{
    return ArduinoFake::getContext()._Serial.getFake(this)->available();
}

int Serial_::peek(void)
{
    return ArduinoFake::getContext()._Serial.getFake(this)->peek();
}

int Serial_::read(void)
{
    return ArduinoFake::getContext()._Serial.getFake(this)->read();
}

void Serial_::flush(void)
{
    ArduinoFake::getContext()._Serial.getFake(this)->flush();
}

size_t Serial_::write(uint8_t c)
{
    return ArduinoFake::getContext()._Serial.getFake(this)->write(c);
}

size_t Serial_::write(const uint8_t *buffer, size_t size)
{
    return ArduinoFake::getContext()._Serial.getFake(this)->write(buffer, size);
}

uint32_t Serial_::baud()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->baud();
}

uint8_t Serial_::stopbits()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->stopbits();
}

uint8_t Serial_::paritytype()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->paritytype();
}

uint8_t Serial_::numbits()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->numbits();
}

bool Serial_::dtr()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->dtr();
}

bool Serial_::rts()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->rts();
}

int32_t Serial_::readBreak()
{
    return ArduinoFake::getContext()._Serial.getFake(this)->readBreak();
}

Serial_ Serial;

#endif // USBCON
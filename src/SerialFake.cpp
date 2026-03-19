#include "ArduinoFake.h"
#include "SerialFake.h"

#if defined(USBCON)

void Serial_::begin(unsigned long baud_count)
{
    ArduinoFakeInstance(this)->begin(baud_count);
}

void Serial_::begin(unsigned long baud_count, byte config)
{
    ArduinoFakeInstance(this)->begin(baud_count, config);
}

void Serial_::end(void)
{
    ArduinoFakeInstance(this)->end();
}

int Serial_::available(void)
{
    return ArduinoFakeInstance(this)->available();
}

int Serial_::peek(void)
{
    return ArduinoFakeInstance(this)->peek();
}

int Serial_::read(void)
{
    return ArduinoFakeInstance(this)->read();
}

void Serial_::flush(void)
{
    ArduinoFakeInstance(this)->flush();
}

size_t Serial_::write(uint8_t c)
{
    return ArduinoFakeInstance(this)->write(c);
}

size_t Serial_::write(const uint8_t *buffer, size_t size)
{
    return ArduinoFakeInstance(this)->write(buffer, size);
}

uint32_t Serial_::baud()
{
    return ArduinoFakeInstance(this)->baud();
}

uint8_t Serial_::stopbits()
{
    return ArduinoFakeInstance(this)->stopbits();
}

uint8_t Serial_::paritytype()
{
    return ArduinoFakeInstance(this)->paritytype();
}

uint8_t Serial_::numbits()
{
    return ArduinoFakeInstance(this)->numbits();
}

bool Serial_::dtr()
{
    return ArduinoFakeInstance(this)->dtr();
}

bool Serial_::rts()
{
    return ArduinoFakeInstance(this)->rts();
}

int32_t Serial_::readBreak()
{
    return ArduinoFakeInstance(this)->readBreak();
}

Serial_ Serial = SerialFakeProxy(ArduinoFakeInstance0(Serial));

#endif // USBCON
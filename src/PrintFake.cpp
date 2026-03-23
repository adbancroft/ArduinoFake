#include "ArduinoFake.h"

int Print::availableForWrite(void)
{
    return ArduinoFakeInstance(this)->availableForWrite();
}

size_t Print::write(const uint8_t *buffer, size_t size)
{
    return ArduinoFakeInstance(this)->write(buffer, size);
}

size_t Print::print(const __FlashStringHelper *ifsh)
{
    return ArduinoFakeInstance(this)->print(ifsh);
}

size_t Print::print(const String &s)
{
    return ArduinoFakeInstance(this)->print(s);
}

size_t Print::print(const char str[])
{
    return ArduinoFakeInstance(this)->print(str);
}

size_t Print::write(uint8_t u)
{
    return ArduinoFakeInstance(this)->write(u);
}

size_t Print::print(char c)
{
    return ArduinoFakeInstance(this)->print(c);
}

size_t Print::print(unsigned char b, int base)
{
    return ArduinoFakeInstance(this)->print(b, base);
}

size_t Print::print(int n, int base)
{
    return ArduinoFakeInstance(this)->print(n, base);
}

size_t Print::print(unsigned int n, int base)
{
    return ArduinoFakeInstance(this)->print(n, base);
}

size_t Print::print(long n, int base)
{
    return ArduinoFakeInstance(this)->print(n, base);
}

size_t Print::print(unsigned long n, int base)
{
    return ArduinoFakeInstance(this)->print(n, base);
}

size_t Print::print(double n, int digits)
{
    return ArduinoFakeInstance(this)->print(n, digits);
}

size_t Print::print(const Printable& x)
{
    return ArduinoFakeInstance(this)->print(x);
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
    return ArduinoFakeInstance(this)->println(ifsh);
}

size_t Print::println(void)
{
    return ArduinoFakeInstance(this)->println();
}

size_t Print::println(const String &s)
{
    return ArduinoFakeInstance(this)->println(s);
}

size_t Print::println(const char c[])
{
    return ArduinoFakeInstance(this)->println(c);
}

size_t Print::println(char c)
{
    return ArduinoFakeInstance(this)->println(c);
}

size_t Print::println(unsigned char b, int base)
{
    return ArduinoFakeInstance(this)->println(b, base);
}

size_t Print::println(int num, int base)
{
    return ArduinoFakeInstance(this)->println(num, base);
}

size_t Print::println(unsigned int num, int base)
{
    return ArduinoFakeInstance(this)->println(num, base);
}

size_t Print::println(long num, int base)
{
    return ArduinoFakeInstance(this)->println(num, base);
}

size_t Print::println(unsigned long num, int base)
{
    return ArduinoFakeInstance(this)->println(num, base);
}

size_t Print::println(double num, int digits)
{
    return ArduinoFakeInstance(this)->println(num, digits);
}

size_t Print::println(const Printable& x)
{
    return ArduinoFakeInstance(this)->println(x);
}

#include "ArduinoFake.h"

int Print::availableForWrite(void)
{
    return ArduinoFake::getContext()._Print.getFake(this)->availableForWrite();
}

size_t Print::write(const uint8_t *buffer, size_t size)
{
    return ArduinoFake::getContext()._Print.getFake(this)->write(buffer, size);
}

size_t Print::print(const __FlashStringHelper *ifsh)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(ifsh);
}

size_t Print::print(const String &s)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(s);
}

size_t Print::print(const char str[])
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(str);
}

size_t Print::write(uint8_t u)
{
    return ArduinoFake::getContext()._Print.getFake(this)->write(u);
}

size_t Print::print(char c)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(c);
}

size_t Print::print(unsigned char b, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(b, base);
}

size_t Print::print(int n, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(n, base);
}

size_t Print::print(unsigned int n, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(n, base);
}

size_t Print::print(long n, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(n, base);
}

size_t Print::print(unsigned long n, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(n, base);
}

size_t Print::print(double n, int digits)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(n, digits);
}

size_t Print::print(const Printable& x)
{
    return ArduinoFake::getContext()._Print.getFake(this)->print(x);
}

size_t Print::println(const __FlashStringHelper *ifsh)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(ifsh);
}

size_t Print::println(void)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println();
}

size_t Print::println(const String &s)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(s);
}

size_t Print::println(const char c[])
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(c);
}

size_t Print::println(char c)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(c);
}

size_t Print::println(unsigned char b, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(b, base);
}

size_t Print::println(int num, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(num, base);
}

size_t Print::println(unsigned int num, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(num, base);
}

size_t Print::println(long num, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(num, base);
}

size_t Print::println(unsigned long num, int base)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(num, base);
}

size_t Print::println(double num, int digits)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(num, digits);
}

size_t Print::println(const Printable& x)
{
    return ArduinoFake::getContext()._Print.getFake(this)->println(x);
}

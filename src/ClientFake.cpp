#include "ArduinoFake.h"
#include <stdexcept>

int Client::connect(IPAddress ip, uint16_t port)
{
    return ArduinoFakeInstance(this)->connect(ip, port);
}

int Client::connect(const char *host, uint16_t port)
{
    return ArduinoFakeInstance(this)->connect(host, port);
}

size_t Client::write(uint8_t value)
{
    return ArduinoFakeInstance(this)->write(value);
}

size_t Client::write(const uint8_t *buf, size_t size)
{
    return ArduinoFakeInstance(this)->write(buf, size);
}

int Client::available()
{
    return ArduinoFakeInstance(this)->available();
}

int Client::read()
{
    return ArduinoFakeInstance(this)->read();
}

int Client::read(uint8_t *buf, size_t size)
{
    return ArduinoFakeInstance(this)->read(buf, size);
}

int Client::peek()
{
    return ArduinoFakeInstance(this)->peek();
}

void Client::flush()
{
    return ArduinoFakeInstance(this)->flush();
}

void Client::stop()
{
    return ArduinoFakeInstance(this)->stop();
}

uint8_t Client::connected()
{
    return ArduinoFakeInstance(this)->connected();
}

Client::operator bool()
{
    return ArduinoFakeInstance(this)->operator bool();
}
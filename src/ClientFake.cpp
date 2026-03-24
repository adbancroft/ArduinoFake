#include "ArduinoFake.h"
#include <stdexcept>

int Client::connect(IPAddress ip, uint16_t port)
{
    return ArduinoFake::getContext()._Client.getFake(this)->connect(ip, port);
}

int Client::connect(const char *host, uint16_t port)
{
    return ArduinoFake::getContext()._Client.getFake(this)->connect(host, port);
}

size_t Client::write(uint8_t value)
{
    return ArduinoFake::getContext()._Client.getFake(this)->write(value);
}

size_t Client::write(const uint8_t *buf, size_t size)
{
    return ArduinoFake::getContext()._Client.getFake(this)->write(buf, size);
}

int Client::available()
{
    return ArduinoFake::getContext()._Client.getFake(this)->available();
}

int Client::read()
{
    return ArduinoFake::getContext()._Client.getFake(this)->read();
}

int Client::read(uint8_t *buf, size_t size)
{
    return ArduinoFake::getContext()._Client.getFake(this)->read(buf, size);
}

int Client::peek()
{
    return ArduinoFake::getContext()._Client.getFake(this)->peek();
}

void Client::flush()
{
    return ArduinoFake::getContext()._Client.getFake(this)->flush();
}

void Client::stop()
{
    return ArduinoFake::getContext()._Client.getFake(this)->stop();
}

uint8_t Client::connected()
{
    return ArduinoFake::getContext()._Client.getFake(this)->connected();
}

Client::operator bool()
{
    return ArduinoFake::getContext()._Client.getFake(this)->operator bool();
}
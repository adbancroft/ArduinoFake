#include "SimpleArduinoFake.h"
#include <stdexcept>

int Client::connect(IPAddress ip, uint16_t port)
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->connect(ip, port);
}

int Client::connect(const char *host, uint16_t port)
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->connect(host, port);
}

size_t Client::write(uint8_t value)
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->write(value);
}

size_t Client::write(const uint8_t *buf, size_t size)
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->write(buf, size);
}

int Client::available()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->available();
}

int Client::read()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->read();
}

int Client::read(uint8_t *buf, size_t size)
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->read(buf, size);
}

int Client::peek()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->peek();
}

void Client::flush()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->flush();
}

void Client::stop()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->stop();
}

uint8_t Client::connected()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->connected();
}

Client::operator bool()
{
    return SimpleArduinoFake::getContext()._Client.getFake(this)->operator bool();
}
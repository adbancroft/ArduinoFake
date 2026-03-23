#include "ArduinoFake.h"

void Stream::setTimeout(unsigned long timeout)
{
    ArduinoFakeInstance(this)->setTimeout(timeout);
}

bool Stream::find(const char *target)
{
    return ArduinoFakeInstance(this)->find(target);
}

bool Stream::find(const char *target, size_t length)
{
    return ArduinoFakeInstance(this)->find(target, length);
}

bool Stream::findUntil(const char *target, const char *terminator)
{
    return ArduinoFakeInstance(this)->findUntil(target, terminator);
}

bool Stream::findUntil(const char *target, size_t targetLen, const char *terminator, size_t termLen)
{
    return ArduinoFakeInstance(this)->findUntil(target, targetLen, terminator, termLen);
}

long Stream::parseInt(LookaheadMode lookahead, char ignore)
{
    return ArduinoFakeInstance(this)->parseInt(lookahead, ignore);
}

float Stream::parseFloat(LookaheadMode lookahead, char ignore)
{
    return ArduinoFakeInstance(this)->parseFloat(lookahead, ignore);
}

size_t Stream::readBytes(char *buffer, size_t length)
{
    return ArduinoFakeInstance(this)->readBytes(buffer, length);
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length)
{
    return ArduinoFakeInstance(this)->readBytesUntil(terminator, buffer, length);
}

String Stream::readString()
{
    return ArduinoFakeInstance(this)->readString();
}

String Stream::readStringUntil(char terminator)
{
    return ArduinoFakeInstance(this)->readStringUntil(terminator);
}

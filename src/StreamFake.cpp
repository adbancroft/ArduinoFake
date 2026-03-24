#include "ArduinoFake.h"

void Stream::setTimeout(unsigned long timeout)
{
    ArduinoFake::getContext()._Stream.getFake(this)->setTimeout(timeout);
}

bool Stream::find(const char *target)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->find(target);
}

bool Stream::find(const char *target, size_t length)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->find(target, length);
}

bool Stream::findUntil(const char *target, const char *terminator)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->findUntil(target, terminator);
}

bool Stream::findUntil(const char *target, size_t targetLen, const char *terminator, size_t termLen)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->findUntil(target, targetLen, terminator, termLen);
}

long Stream::parseInt(LookaheadMode lookahead, char ignore)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->parseInt(lookahead, ignore);
}

float Stream::parseFloat(LookaheadMode lookahead, char ignore)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->parseFloat(lookahead, ignore);
}

size_t Stream::readBytes(char *buffer, size_t length)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->readBytes(buffer, length);
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->readBytesUntil(terminator, buffer, length);
}

String Stream::readString()
{
    return ArduinoFake::getContext()._Stream.getFake(this)->readString();
}

String Stream::readStringUntil(char terminator)
{
    return ArduinoFake::getContext()._Stream.getFake(this)->readStringUntil(terminator);
}

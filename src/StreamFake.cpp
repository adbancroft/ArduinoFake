#include "ArduinoFake.h"
#include "StreamFake.h"

void Stream::setTimeout(unsigned long timeout)
{
    ArduinoFakeInstance(Stream, this)->setTimeout(timeout);
}

bool Stream::find(const char *target)
{
    return ArduinoFakeInstance(Stream, this)->find(target);
}

bool Stream::find(const char *target, size_t length)
{
    return ArduinoFakeInstance(Stream, this)->find(target, length);
}

bool Stream::findUntil(const char *target, char *terminator)
{
    return ArduinoFakeInstance(Stream, this)->findUntil(target, terminator);
}

bool Stream::findUntil(const char *target, size_t targetLen, const char *terminator, size_t termLen)
{
    return ArduinoFakeInstance(Stream, this)->findUntil(target, targetLen, terminator, termLen);
}

long Stream::parseInt(LookaheadMode lookahead, char ignore)
{
    return ArduinoFakeInstance(Stream, this)->parseInt(lookahead, ignore);
}

float Stream::parseFloat(LookaheadMode lookahead, char ignore)
{
    return ArduinoFakeInstance(Stream, this)->parseFloat(lookahead, ignore);
}

size_t Stream::readBytes(char *buffer, size_t length)
{
    return ArduinoFakeInstance(Stream, this)->readBytes(buffer, length);
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length)
{
    return ArduinoFakeInstance(Stream, this)->readBytesUntil(terminator, buffer, length);
}

String Stream::readString()
{
    return ArduinoFakeInstance(Stream, this)->readString();
}

String Stream::readStringUntil(char terminator)
{
    return ArduinoFakeInstance(Stream, this)->readStringUntil(terminator);
}

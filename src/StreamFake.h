#pragma once

#include "PrintFake.h"
#include "arduino/Stream.h"

#ifndef NO_IGNORE_CHAR
  #define NO_IGNORE_CHAR  '\x01' // a char not found in a valid ASCII numeric field
#endif

struct StreamFake : public PrintFake
{
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;

    virtual void setTimeout(unsigned long timeout) = 0;
    virtual unsigned long getTimeout(void) = 0;

    virtual bool find(const char *target) = 0;

    virtual bool find(const char *target, size_t length) = 0;

    virtual bool findUntil(const char *target, const char *terminator) = 0;

    virtual bool findUntil(const char *target, size_t targetLen, const char *terminate, size_t termLen) = 0;

    virtual long parseInt(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) = 0;

    virtual float parseFloat(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) = 0;

    virtual size_t readBytes(char *buffer, size_t length) = 0;

    virtual size_t readBytesUntil(char terminator, char *buffer, size_t length) = 0;

    virtual String readString() = 0;
    virtual String readStringUntil(char terminator) = 0;
};

class StreamFakeProxy : public Stream, public PrintFakeProxy
{
    private:
        StreamFake* streamFake;

    public:
        StreamFakeProxy(StreamFake* fake) : PrintFakeProxy(fake)
        {
            streamFake = fake;
        }

        size_t write(uint8_t value) override
        {
            return streamFake->write(value);
        }

        int available() override
        {
            return streamFake->available();
        }

        int read() override
        {
            return streamFake->read();
        }

        int peek() override
        {
            return streamFake->peek();
        }

        void flush() override
        {
            streamFake->flush();
        }

        void setTimeout(unsigned long timeout) override
        {
            getFake()->setTimeout(timeout);
        }
    
        unsigned long getTimeout(void) override
        {
            return getFake()->getTimeout();
        }

        StreamFake* getFake()
        {
            return streamFake;
        }
};
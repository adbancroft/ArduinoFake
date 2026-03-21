#pragma once

#include "StreamFake.h"
#include "arduino/USBAPI.h"

#if defined(USBCON)

using SerialFake = Serial_;

class SerialFakeProxy : public StreamFakeProxy<SerialFake>
{
public:
    SerialFakeProxy(SerialFake* fake) : StreamFakeProxy<SerialFake>(fake)
    {
    }
};

#endif // USBCON

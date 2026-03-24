#pragma once
// clang-format off

#if !defined(USBCON)
    #error Add "-D USBCON" to the compiler command line
#endif

#include <Stream.h>
#include <USBAPI.h>
#include <Wire.h>
#include <Client.h>
#include <Print.h>
#include <SPI.h>
#include <EEPROM.h>

#include "ArduinoFakeOverride.h"
#include "FunctionFake.h"

namespace ArduinoFake {

class Context
{
    details::FakeOverride_t _fakeOverrides;
public:
    details::ArduinoFake_t<details::FunctionFake> _Function;
    details::OverrideableArduinoFake_t<Serial_> _Serial;
    details::OverrideableArduinoFake_t<TwoWire> _Wire;
    details::OverrideableArduinoFake_t<Stream> _Stream;
    details::OverrideableArduinoFake_t<Client> _Client;
    details::OverrideableArduinoFake_t<Print> _Print;
    details::OverrideableArduinoFake_t<SPIClass> _SPI;
    details::OverrideableArduinoFake_t<EEPROMClass> _EEPROM;

    Context()
        : _fakeOverrides()
        , _Function()
        , _Serial(_fakeOverrides)
        , _Wire(_fakeOverrides)
        , _Stream(_fakeOverrides)
        , _Client(_fakeOverrides)
        , _Print(_fakeOverrides)
        , _SPI(_fakeOverrides)
        , _EEPROM(_fakeOverrides)
    {
        this->Reset();
    }

    void Reset(void)
    {
        _Function.Reset();
        _Serial.Reset();
        _Wire.Reset();
        _Stream.Reset();
        _Client.Reset();
        _Print.Reset();
        _SPI.Reset();
        _EEPROM.Reset();

        _fakeOverrides.Reset();
        _fakeOverrides.setOverride(&::Serial, &_Serial);
        _fakeOverrides.setOverride(&::Wire, &_Wire);
        _fakeOverrides.setOverride(&::SPI, &_SPI);
        _fakeOverrides.setOverride(&::EEPROM, &_EEPROM);
    }
};

Context& getContext();

}

// clang-format on
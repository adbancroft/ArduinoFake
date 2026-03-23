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

/// @cond
// Implementation details

#define _ArduinoFakeGetMock(mock) \
    getArduinoFakeContext()._##mock

#define _ArduinoFakeGetFunction() _ArduinoFakeGetMock(Function)
#define _ArduinoFakeGetSerial() _ArduinoFakeGetMock(Serial)
#define _ArduinoFakeGetWire() _ArduinoFakeGetMock(Wire)
#define _ArduinoFakeGetSPI() _ArduinoFakeGetMock(SPI)
#define _ArduinoFakeGetEEPROM() _ArduinoFakeGetMock(EEPROM)
#define _ArduinoFakeGetStream() _ArduinoFakeGetMock(Stream)
#define _ArduinoFakeGetClient() _ArduinoFakeGetMock(Client)
#define _ArduinoFakeGetPrint() _ArduinoFakeGetMock(Print)
#define _ArduinoFakeGet() _ArduinoFakeGetMock(Function)

/// @endcond

#define ArduinoFakeReset() \
    getArduinoFakeContext().Reset()

#define ArduinoFakeInstance(mock, ...) \
    _ArduinoFakeGetMock(mock).getFake(__VA_ARGS__)

#define ArduinoFake(mock) _ArduinoFakeGet##mock()

class ArduinoFakeContext
{
public:
    ArduinoFake::details::FakeOverride_t _fakeOverrides;
    ArduinoFake::details::ArduinoFake_t<ArduinoFake::details::FunctionFake> _Function;
    ArduinoFake::details::OverrideableArduinoFake_t<Serial_> _Serial;
    ArduinoFake::details::OverrideableArduinoFake_t<TwoWire> _Wire;
    ArduinoFake::details::OverrideableArduinoFake_t<Stream> _Stream;
    ArduinoFake::details::OverrideableArduinoFake_t<Client> _Client;
    ArduinoFake::details::OverrideableArduinoFake_t<Print> _Print;
    ArduinoFake::details::OverrideableArduinoFake_t<SPIClass> _SPI;
    ArduinoFake::details::OverrideableArduinoFake_t<EEPROMClass> _EEPROM;

    ArduinoFakeContext()
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

ArduinoFakeContext& getArduinoFakeContext();

// clang-format on
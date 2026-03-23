#pragma once
// clang-format off

#if !defined(USBCON)
    #error Add "-D USBCON" to the compiler command line
#endif

#include <unordered_map>
#include <cstring>
#include <cstdint>
#include <stdexcept>
#if defined(abs)
#undef abs
#endif
#include <single_header/standalone/fakeit.hpp>

#include <Arduino.h>
#include <Stream.h>
#include <USBAPI.h>
#include <Wire.h>
#include <Client.h>
#include <Print.h>
#include <SPI.h>
#include <EEPROM.h>

#include "FunctionFake.h"

#define ArduinoFakeReset() \
    getArduinoFakeContext()->Reset()

#define _ArduinoFakeGetMock(mock) \
    getArduinoFakeContext()->_##mock

#define ArduinoFakeInstance(mock, ...) \
    _ArduinoFakeGetMock(mock).getFake(__VA_ARGS__)

#define _ArduinoFakeGetFunction() _ArduinoFakeGetMock(Function)
#define _ArduinoFakeGetSerial() _ArduinoFakeGetMock(Serial)
#define _ArduinoFakeGetWire() _ArduinoFakeGetMock(Wire)
#define _ArduinoFakeGetSPI() _ArduinoFakeGetMock(SPI)
#define _ArduinoFakeGetEEPROM() _ArduinoFakeGetMock(EEPROM)
#define _ArduinoFakeGetStream() _ArduinoFakeGetMock(Stream)
#define _ArduinoFakeGetClient() _ArduinoFakeGetMock(Client)
#define _ArduinoFakeGetPrint() _ArduinoFakeGetMock(Print)
#define _ArduinoFakeGet() _ArduinoFakeGetMock(Function)

#define ArduinoFake(mock) _ArduinoFakeGet##mock()

// Access fakeit::Mock<T>.get()
// There is no equivalent in fakeit since Mock is a template 
struct IFake
{
    // Ideally this have a templated return type, but then it can't be 
    // virtual :-(
    // We need this to be virtual to store instances in a map.
    virtual void* toFake(void) = 0;
};

template <class FakeT, typename BaseT = fakeit::Mock<FakeT>>
struct ArduinoFake_t : public BaseT, IFake
{
    // Typed access to the mocked object
    FakeT* getFake(void)
    {
        return &fakeit::Mock<FakeT>::get();
    }

    // Untyped access to the mocked object
    virtual void* toFake(void) override
    {
        return getFake();
    }
};

// Maps from global instances to the equivalent IFake.
//
// Required to respect inherited classes.
// E.g. Stream has 2 derived classes, Serial_ & TwoWire. Each has a global instance, Serial & Wire.
// We want to allow different mock implementations *of the same Stream method* for Serial_ & TwoWire
// and have the global instances use those different mocks.
class FakeOverride_t
{
public:
    void Reset(void)
    {
        _mapping.clear();
    }

    IFake *getOverride(void *instance)
    {
        auto iter = _mapping.find(instance);
        return iter==_mapping.end() ? nullptr : iter->second;
    }

    void setOverride(void *instance, IFake *override)
    {
        _mapping[instance] = override;
    }

private:
    std::unordered_map<void*, IFake*> _mapping;
};

template <class FakeT, typename BaseT = ArduinoFake_t<FakeT>>
struct OverrideableArduinoFake_t : public BaseT
{
    FakeOverride_t &_overrides;

    OverrideableArduinoFake_t(FakeOverride_t &overrides)
        : BaseT()
        , _overrides(overrides)
    {
    }
   
    template <class ArduinoT>
    FakeT* getFake(ArduinoT *instance)
    {
        auto *pOverride = _overrides.getOverride(instance);
        if (pOverride!=nullptr) {
            return (FakeT*)pOverride->toFake();
        }
        return getFake();
    }

    using BaseT::getFake;
};

class ArduinoFakeContext
{
public:
    FakeOverride_t _fakeOverrides;
    ArduinoFake_t<FunctionFake> _Function;
    OverrideableArduinoFake_t<Serial_> _Serial;
    OverrideableArduinoFake_t<TwoWire> _Wire;
    OverrideableArduinoFake_t<Stream> _Stream;
    OverrideableArduinoFake_t<Client> _Client;
    OverrideableArduinoFake_t<Print> _Print;
    OverrideableArduinoFake_t<SPIClass> _SPI;
    OverrideableArduinoFake_t<EEPROMClass> _EEPROM;

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

ArduinoFakeContext* getArduinoFakeContext();

// clang-format on
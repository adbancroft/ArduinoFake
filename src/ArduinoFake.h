#pragma once
// clang-format off

#if !defined(UBRRH) && !defined(UBRR0H) && !defined(USBCON)
    #define USBCON
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

using PrintFake = Print;
using ClientFake = Client;
using StreamFake = Stream;
using SerialFake = Serial_;
using WireFake = TwoWire;
using SPIFake = SPIClass;
using EEPROMFake = EEPROMClass;

#define CONCAT2(x,y) x##y
#define CONCAT(x,y) CONCAT2(x,y)

// These map a Arduino class name (E.g. "SPIClass") to
// the corresponding fake member name (E.g. "SPI")
#define _ClazzToFakePrint() Print
#define _ClazzToFakeClient() Client
#define _ClazzToFakeStream() Stream
#define _ClazzToFakeSerial_() Serial
#define _ClazzToFakeTwoWire() Wire
#define _ClazzToFakeSPIClass() SPI
#define _ClazzToFakeEEPROMClass() EEPROM
#define _ClazzToFake(clazz) _ClazzToFake##clazz()

#define ArduinoFakeReset() \
    getArduinoFakeContext()->Reset()

 #define ArduinoFakeInstance0(mock) \
    getArduinoFakeContext()->mock()

#define ArduinoFakeInstance(clazz) \
    getArduinoFakeContext()->getFake(clazz)

#define _ArduinoFakeGetMock(mock) \
    getArduinoFakeContext()->_##mock

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
    // Proxy to fake
    template <class ArduinoT>
    FakeT* getFake(ArduinoT *instance)
    {
        return static_cast<FakeT*>(toFake());
    }

    // Get the 'real' fake - the one that is actually mocked.
    virtual void* toFake(void) override
    {
        return &fakeit::Mock<FakeT>::get();
    }
};

// Maps from global instances to the equivalent IFake.
// E.g. Serial => SerialFake
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
        return BaseT::getFake(instance);
    }
};

class ArduinoFakeContext
{
public:
    FakeOverride_t _fakeOverrides;
    fakeit::Mock<FunctionFake> _Function;
    OverrideableArduinoFake_t<SerialFake> _Serial;
    OverrideableArduinoFake_t<WireFake> _Wire;
    OverrideableArduinoFake_t<StreamFake> _Stream;
    OverrideableArduinoFake_t<ClientFake> _Client;
    OverrideableArduinoFake_t<PrintFake> _Print;
    OverrideableArduinoFake_t<SPIFake> _SPI;
    OverrideableArduinoFake_t<EEPROMFake> _EEPROM;
    
#define _ArduinoFakeInstanceGetter1(mock) \
    mock##Fake* mock() \
    { \
        return &this->_##mock.get(); \
    }

    _ArduinoFakeInstanceGetter1(Print)
    _ArduinoFakeInstanceGetter1(Stream)
    _ArduinoFakeInstanceGetter1(Serial)
    _ArduinoFakeInstanceGetter1(Wire)
    _ArduinoFakeInstanceGetter1(Client)
    _ArduinoFakeInstanceGetter1(Function)
    _ArduinoFakeInstanceGetter1(SPI)
    _ArduinoFakeInstanceGetter1(EEPROM)

#undef _ArduinoFakeInstanceGetter1

#define _ArduinoFakeInstanceGetter2(clazz) \
    CONCAT(_ClazzToFake(clazz), Fake)* getFake(class clazz* instance) \
    { \
        return this->CONCAT(_, _ClazzToFake(clazz)).getFake(instance); \
    }

    _ArduinoFakeInstanceGetter2(Print)
    _ArduinoFakeInstanceGetter2(Client)
    _ArduinoFakeInstanceGetter2(Stream)
    _ArduinoFakeInstanceGetter2(Serial_)
    _ArduinoFakeInstanceGetter2(TwoWire)
    _ArduinoFakeInstanceGetter2(SPIClass)
    _ArduinoFakeInstanceGetter2(EEPROMClass)

#undef _ArduinoFakeInstanceGetter2

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
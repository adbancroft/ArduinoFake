#pragma once
// clang-format off

#if !defined(UBRRH) && !defined(UBRR0H) && !defined(USBCON)
    #define USBCON
#endif

#include <unordered_map>
#include <cstring>
#include <cstdint>
#include <stdexcept>
#include "fakeit.hpp"

#include "arduino/Arduino.h"

#include "Function.h"
#include "Stream.h"
#include "Serial.h"
#include "Wire.h"
#include "Client.h"
#include "Print.h"
#include "SPI.h"
#include "EEPROM.h"

#define ArduinoFakeReset() \
    getArduinoFakeContext()->reset()

#define ArduinoFakeInstance(mock, ...) \
    getArduinoFakeContext()->mock(__VA_ARGS__)

#define ArduinoFakeMock(mock) \
    new mock##FakeProxy(ArduinoFakeInstance(mock))

#define _ArduinoFakeGetMock(mock) \
    getArduinoFakeContext()->_##mock.Fake

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

template <class FakeT>
struct ArduinoFake_t
{
    fakeit::Mock<FakeT> Fake;

    void reset(void)
    {
        Fake.Reset();
    }

    FakeT* getFake(void)
    {
        return &Fake.get();
    }
};

template <class FakeT, class ProxyT, typename BaseT = ArduinoFake_t<FakeT>>
struct ProxiedArduinoFake_t : public BaseT
{
    // Pull in base class getFake()
    using BaseT::getFake;
    
    template <class ArduinoT>
    FakeT* getFake(ArduinoT *instance)
    {
        if (dynamic_cast<ProxyT*>(instance)) {
            return dynamic_cast<ProxyT*>(instance)->getFake();
        }
        throw std::runtime_error("Unknown instance");
    }
};

class FakeOverride_t
{
public:
    void reset(void)
    {
        _mapping.clear();
    }

    void *getOverride(void *instance)
    {
        auto iter = _mapping.find(instance);
        return iter==_mapping.end() ? nullptr : iter->second;
    }

    void setOverride(void *instance, void *override)
    {
        _mapping[instance] = override;
    }

private:
    std::unordered_map<void*, void*> _mapping;
};

template <class FakeT, class ProxyT, typename BaseT = ProxiedArduinoFake_t<FakeT, ProxyT>>
struct OverrideableProxiedArduinoFake_t : public BaseT
{
    FakeOverride_t &_overrides;

    OverrideableProxiedArduinoFake_t(FakeOverride_t &overrides)
        : BaseT()
        , _overrides(overrides)
    {
    }

    // Pull in base class getFake()
    using BaseT::getFake;
    
    template <class ArduinoT>
    FakeT* getFake(ArduinoT *instance)
    {
        ArduinoFake_t<FakeT> *pOverride = static_cast<ArduinoFake_t<FakeT> *>(_overrides.getOverride(instance));
        if (pOverride!=nullptr) {
            return pOverride->getFake();
        }
        return BaseT::getFake(instance);
    }
};

class ArduinoFakeContext
{
public:
    FakeOverride_t _fakeOverrides;
    ArduinoFake_t<FunctionFake> _Function;
    OverrideableProxiedArduinoFake_t<SerialFake, SerialFakeProxy> _Serial;
    OverrideableProxiedArduinoFake_t<WireFake, WireFakeProxy> _Wire;
    OverrideableProxiedArduinoFake_t<StreamFake, StreamFakeProxy> _Stream;
    OverrideableProxiedArduinoFake_t<ClientFake, ClientFakeProxy> _Client;
    OverrideableProxiedArduinoFake_t<PrintFake, PrintFakeProxy> _Print;
    OverrideableProxiedArduinoFake_t<SPIFake, SPIFakeProxy> _SPI;
    OverrideableProxiedArduinoFake_t<EEPROMFake, EEPROMFakeProxy> _EEPROM;
    
#define _ArduinoFakeInstanceGetter1(mock) \
    mock##Fake* mock() \
    { \
        return this->_##mock.getFake(); \
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

#define _ArduinoFakeInstanceGetter2(name, clazz) \
    name##Fake* name(class clazz* instance) \
    { \
        return this->_##name.getFake(instance); \
    }

    _ArduinoFakeInstanceGetter2(Print, Print)
    _ArduinoFakeInstanceGetter2(Client, Client)
    _ArduinoFakeInstanceGetter2(Stream, Stream)
    _ArduinoFakeInstanceGetter2(Serial, Serial_)
    _ArduinoFakeInstanceGetter2(Wire, TwoWire)
    _ArduinoFakeInstanceGetter2(SPI, SPIClass)
    _ArduinoFakeInstanceGetter2(EEPROM, EEPROMClass)

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
        this->reset();
    }

    void reset(void)
    {
        _Function.reset();
        _Serial.reset();
        _Wire.reset();
        _Stream.reset();
        _Client.reset();
        _Print.reset();
        _SPI.reset();
        _EEPROM.reset();

        _fakeOverrides.reset();
        _fakeOverrides.setOverride(&::Serial, &_Serial);
        _fakeOverrides.setOverride(&::Wire, &_Wire);
        _fakeOverrides.setOverride(&::SPI, &_SPI);
        _fakeOverrides.setOverride(&::EEPROM, &_EEPROM);
    }

};

ArduinoFakeContext* getArduinoFakeContext();

// clang-format on
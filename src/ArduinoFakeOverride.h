/**
 * @file
 * @brief Support code for mocking global Arduino instances that form part of an inheritance hierarchy
 * 
 * Required to respect inherited classes.
 * E.g. Stream has 2 derived classes, Serial_ & TwoWire. Each has a *global* instance, Serial & Wire.
 * We want to allow different mock implementations *of the same Stream method* for Serial_ & TwoWire
 * and have the global instances use those different mocks.
 * 
  */
#pragma once

#include <unordered_map>
#if defined(abs)
#undef abs
#endif
#include <single_header/standalone/fakeit.hpp>

namespace SimpleArduinoFake {

namespace details {

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

}
}
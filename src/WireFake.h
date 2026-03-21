#pragma once

#include "StreamFake.h"
#include "arduino/Wire.h"

using WireFake = TwoWire;

class WireFakeProxy : public StreamFakeProxy<TwoWire> {
public:
  WireFakeProxy(WireFake *fake) : StreamFakeProxy<TwoWire>(fake) { }
};
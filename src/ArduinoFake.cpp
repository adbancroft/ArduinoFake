#include "ArduinoFake.h"

namespace ArduinoFake {

Context& getContext()
{
    static Context arduinoFakeContext;
    return arduinoFakeContext;
}

}
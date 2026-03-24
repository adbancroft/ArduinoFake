#include "SimpleArduinoFake.h"

namespace SimpleArduinoFake {

Context& getContext()
{
    static Context arduinoFakeContext;
    return arduinoFakeContext;
}

}
#include "ArduinoFake.h"

ArduinoFakeContext& getArduinoFakeContext()
{
    static ArduinoFakeContext arduinoFakeContext;
    return arduinoFakeContext;
}

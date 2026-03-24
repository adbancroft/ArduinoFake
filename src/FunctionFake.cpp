#include "FunctionFake.h"
#include "SimpleArduinoFake.h"

void init(void)
{
    SimpleArduinoFake::getContext()._Function.getFake()->init();
}

void pinMode(uint8_t pin, uint8_t mode)
{
    SimpleArduinoFake::getContext()._Function.getFake()->pinMode(pin, mode);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    SimpleArduinoFake::getContext()._Function.getFake()->digitalWrite(pin, val);
}

int digitalRead(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->digitalRead(pin);
}

int analogRead(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->analogRead(pin);
}

void analogWrite(uint8_t pin, int val)
{
    SimpleArduinoFake::getContext()._Function.getFake()->analogWrite(pin, val);
}

void analogReference(uint8_t mode)
{
    SimpleArduinoFake::getContext()._Function.getFake()->analogReference(mode);
}

void analogReadResolution(uint8_t mode)
{
    SimpleArduinoFake::getContext()._Function.getFake()->analogReadResolution(mode);
}

unsigned long millis(void)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->millis();
}

unsigned long micros(void)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->micros();
}

void delay(unsigned long value)
{
    SimpleArduinoFake::getContext()._Function.getFake()->delay(value);
}

void delayMicroseconds(unsigned int us)
{
    SimpleArduinoFake::getContext()._Function.getFake()->delayMicroseconds(us);
}

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->pulseIn(pin, state, timeout);
}

unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->pulseInLong(pin, state, timeout);
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    SimpleArduinoFake::getContext()._Function.getFake()->shiftOut(dataPin, clockPin, bitOrder, val);
}

uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
    return SimpleArduinoFake::getContext()._Function.getFake()->shiftIn(dataPin, clockPin, bitOrder);
}

void detachInterrupt(uint8_t interruptNum) {
    SimpleArduinoFake::getContext()._Function.getFake()->detachInterrupt(interruptNum);
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
	SimpleArduinoFake::getContext()._Function.getFake()->attachInterrupt(interruptNum, userFunc, mode);
}

void cli(void) {
    SimpleArduinoFake::getContext()._Function.getFake()->cli();
}

void sei(void) {
    SimpleArduinoFake::getContext()._Function.getFake()->sei();
}

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
    SimpleArduinoFake::getContext()._Function.getFake()->tone(pin, frequency, duration);
}

void noTone(uint8_t pin)
{
    SimpleArduinoFake::getContext()._Function.getFake()->noTone(pin);
}

long random(long max)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->random(max);
}

long random(long min, long max)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->random(min, max);
}

void randomSeed(unsigned long seed)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->randomSeed(seed);
}

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->map(value, fromLow, fromHigh, toLow, toHigh);
}

void yield()
{
    SimpleArduinoFake::getContext()._Function.getFake()->yield();
}


uint8_t digitalPinToPort(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->digitalPinToPort(pin);
}
uint8_t digitalPinToBitMask(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->digitalPinToBitMask(pin);
}
uint8_t digitalPinToTimer(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->digitalPinToTimer(pin);
}
volatile uint8_t * portOutputRegister(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->portOutputRegister(pin);
}
volatile uint8_t * portInputRegister(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->portInputRegister(pin);
}
volatile uint8_t * portModeRegister(uint8_t pin)
{
    return SimpleArduinoFake::getContext()._Function.getFake()->portModeRegister(pin);
}

# ArduinoFake

[![Build](https://github.com/adbancroft/SimpleArduinoFake/actions/workflows/check.yaml/badge.svg)](https://github.com/adbancroft/SimpleArduinoFake/actions/workflows/check.yml)

`SimpleArduinoFake` is a simple mocking framework for Arduino,, based on [FakeIt](https://github.com/eranpeer/FakeIt). Its goal is to allow unit testing of your Arduino project *natively*, with no Arduino. This supports:
1. Complex testing that might exceed physical board limits. E.g. RAM
2. Unit test coverage, which is not possible on a physical board.

This project is a hard fork of [`ArduinoFake`](https://github.com/FabioBatSilva/ArduinoFake), with some simplifications and bug fixes:
1. No proxies. Arduino classes (E.g. `Stream`) are mocked directly rather than via a proxy object, so code is DRY
2. No [object slicing](https://github.com/FabioBatSilva/ArduinoFake/issues/85)
3. No [memory leaks](https://github.com/FabioBatSilva/ArduinoFake/issues/86)
5. More modern code style for a simpler code base: no macros, use of namespaces & no dynamic memory allocation
5. Compiles on Windows, using mingw64.

## Quickstart

### Includes

You should include the following header in your test file:

```c++
#include <SimpleArduinoFake.h>
```

### Stubbing

Assuming we have the following arduino code:
```c++
// src/main.cpp
void loop()
{
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);
    // wait for a second
    delay(100);
    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);
     // wait for a second
    delay(100);
}
```

It can be tested using `SimpleArduinoFake`:
```c++
#include <SimpleArduinoFake.h>

using namespace fakeit;

// test/test_main.cpp
void test_loop(void)
{
	auto &functionFake = SimpleArduinoFake::getContext()._Function;
    
	When(Method(functionFake, digitalWrite)).AlwaysReturn();
    When(Method(functionFake, delay)).AlwaysReturn();

    loop();

    Verify(Method(functionFake, digitalWrite).Using(LED_BUILTIN, HIGH)).Once();
    Verify(Method(functionFake, digitalWrite).Using(LED_BUILTIN, LOW)).Once();
    Verify(Method(functionFake, delay).Using(100)).Exactly(2_Times);
}
```

Look at the [examples](./examples) or the [tests](./test) for examples.

## Troubleshooting

If you get a segfault while running your unit tests, eg:

```
Program errored with 3221225477 code
```

Check to make sure you have stubbed **all** the Arduino methods you are calling.

# Contributing
Contributions are welcome:
1. The project uses [PlatformIO](https://platformio.org/) for building, unit testing and CI.
2. Make sure your changes are covered by unit tests.
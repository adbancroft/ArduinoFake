# Arduino

Files present in this directory were extracted from [arduino](https://github.com/arduino) *and modified* to support mocking:
1. The `virtual` keyword has been added to public methods. 
2. Convert some macros to free functions. E.g. `portOutputRegister`
3. Some parameters declared `const`. E.g. `char *`

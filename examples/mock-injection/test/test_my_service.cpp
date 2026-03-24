#include <Arduino.h>
#include <unity.h>

using namespace fakeit;

#include "MyService.h"

void test_connect(void)
{
    When(Method(ArduinoFake::getContext()._Client, stop)).AlwaysReturn();
    When(Method(ArduinoFake::getContext()._Client, available)).Return(1, 1, 1, 0);
    When(OverloadedMethod(ArduinoFake::getContext()._Client, read, int())).Return(2, 0, 0);
    When(OverloadedMethod(ArduinoFake::getContext()._Client, println, size_t())).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake::getContext()._Client, println, size_t(const char *))).AlwaysReturn();
    When(OverloadedMethod(ArduinoFake::getContext()._Client, connect, int(const char*, uint16_t))).Return(1);

    Client * clientMock(ArduinoFake::getContext()._Client.getFake());

    MyService service(clientMock);

    String response = service.request("myserver.com");
    TEST_ASSERT_EQUAL(3, response.length());
    TEST_ASSERT_TRUE(response.equals("200"));

    Verify(Method(ArduinoFake::getContext()._Client, stop)).Once();
    Verify(Method(ArduinoFake::getContext()._Client, available)).Exactly(4_Times);
    Verify(OverloadedMethod(ArduinoFake::getContext()._Client, read, int())).Exactly(3_Times);

    Verify(OverloadedMethod(ArduinoFake::getContext()._Client, println, size_t())).Once();
    Verify(OverloadedMethod(ArduinoFake::getContext()._Client, println, size_t(const char [])).Using((const char *)"STATUS")).Never();
    Verify(OverloadedMethod(ArduinoFake::getContext()._Client, connect, int(const char[], uint16_t)).Using((const char *)"myserver.com", 80)).Once();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_connect);

    return UNITY_END();
}

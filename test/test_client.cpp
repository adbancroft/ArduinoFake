#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

static const char * localhost = "localhost";

using namespace fakeit;

class MyService
{
    public:
        MyService(Client* client)
        {
            _client = client;
        }

        size_t send(uint16_t value)
        {
            return _client->write(value);
        }

    private:
        Client* _client;
};

static void test_basics(void)
{
    auto &clientFake = SimpleArduinoFake::getContext()._Client;
    When(Method(clientFake, stop)).Return();
    When(Method(clientFake, peek)).Return(2);
    When(Method(clientFake, flush)).Return();
    When(Method(clientFake, connected)).Return(0, 1);
    When(OverloadedMethod(clientFake, connect, int(const char*, uint16_t))).Return(1);

    Client * client(clientFake.getFake());

    TEST_ASSERT_EQUAL(0, client->connected());
    TEST_ASSERT_EQUAL(1, client->connect(localhost, 8080));
    TEST_ASSERT_EQUAL(1, client->connected());
    TEST_ASSERT_EQUAL(2, client->peek());

    client->flush();
    client->stop();

    Verify(Method(clientFake, stop)).Once();
    Verify(Method(clientFake, peek)).Once();
    Verify(Method(clientFake, flush)).Once();
    Verify(Method(clientFake, connected)).Exactly(2_Times);
    Verify(OverloadedMethod(clientFake, connect, int(const char*, uint16_t)).Using(localhost, 8080)).Once();
}

static void test_connect(void)
{
    auto &clientFake = SimpleArduinoFake::getContext()._Client;
    When(OverloadedMethod(clientFake, connect, int(const char*, uint16_t))).Return(1, 0);
    When(OverloadedMethod(clientFake, connect, int(IPAddress, uint16_t))).Return(0, 1);

    IPAddress ipAddress1(62, 145, 182, 225);
    IPAddress ipAddress2(221, 155, 131, 19);

    Client * client(clientFake.getFake());

    TEST_ASSERT_EQUAL(1, client->connect(localhost, 8080));
    TEST_ASSERT_EQUAL(0, client->connect(localhost, 80));

    TEST_ASSERT_EQUAL(0, client->connect(ipAddress1, 8080));
    TEST_ASSERT_EQUAL(1, client->connect(ipAddress2, 8080));

    Verify(OverloadedMethod(clientFake, connect, int(const char*, uint16_t)).Using(localhost, 8080)).Once();
    Verify(OverloadedMethod(clientFake, connect, int(const char*, uint16_t)).Using(localhost, 80)).Once();

    Verify(OverloadedMethod(clientFake, connect, int(IPAddress, uint16_t)).Using(ipAddress1, 8080)).Once();
    Verify(OverloadedMethod(clientFake, connect, int(IPAddress, uint16_t)).Using(ipAddress2, 8080)).Once();
}

static void test_write(void)
{
    uint8_t val1 = 0x0;
    uint8_t val2 = 0x1;

    const uint8_t* ptr1 = &val1;
    const uint8_t* ptr2 = &val2;

    auto &clientFake = SimpleArduinoFake::getContext()._Client;
    When(OverloadedMethod(clientFake, write, size_t(uint8_t))).Return(1, 0);
    When(OverloadedMethod(clientFake, write, size_t(const uint8_t*, size_t))).Return(0, 1);

    Client * client(clientFake.getFake());

    TEST_ASSERT_EQUAL(1, client->write(val1));
    TEST_ASSERT_EQUAL(0, client->write(val2));

    TEST_ASSERT_EQUAL(0, client->write(ptr1, 2));
    TEST_ASSERT_EQUAL(1, client->write(ptr2, 3));

    Verify(OverloadedMethod(clientFake, write, size_t(uint8_t)).Using(val1)).Once();
    Verify(OverloadedMethod(clientFake, write, size_t(uint8_t)).Using(val2)).Once();

    Verify(OverloadedMethod(clientFake, write, size_t(const uint8_t*, size_t)).Using(ptr1, 2)).Once();
    Verify(OverloadedMethod(clientFake, write, size_t(const uint8_t*, size_t)).Using(ptr2, 3)).Once();
}

static void test_read(void)
{
    uint8_t val1 = 0x0;
    uint8_t val2 = 0x1;

    uint8_t* ptr1 = &val1;
    uint8_t* ptr2 = &val2;

    auto &clientFake = SimpleArduinoFake::getContext()._Client;
    When(OverloadedMethod(clientFake, read, int())).Return(10, 20);
    When(OverloadedMethod(clientFake, read, int(uint8_t*, size_t))).Return(30, 400);

    Client * client(clientFake.getFake());

    TEST_ASSERT_EQUAL(10, client->read());
    TEST_ASSERT_EQUAL(20, client->read());

    TEST_ASSERT_EQUAL(30, client->read(ptr1, 2));
    TEST_ASSERT_EQUAL(400, client->read(ptr2, 3));

    Verify(OverloadedMethod(clientFake, read, int())).Exactly(2_Times);

    Verify(OverloadedMethod(clientFake, read, int(uint8_t*, size_t)).Using(ptr1, 2)).Once();
    Verify(OverloadedMethod(clientFake, read, int(uint8_t*, size_t)).Using(ptr2, 3)).Once();
}

static void test_inject_instance(void)
{
    uint8_t val1 = 0x0;
    uint8_t val2 = 0x1;

    auto &clientFake = SimpleArduinoFake::getContext()._Client;
    When(OverloadedMethod(clientFake, write, size_t(uint8_t))).Return(11, 22);

    Client * client(clientFake.getFake());

    MyService service(client);

    TEST_ASSERT_EQUAL(11, service.send(val1));
    TEST_ASSERT_EQUAL(22, service.send(val2));

    Verify(OverloadedMethod(clientFake, write, size_t(uint8_t)).Using(val1)).Once();
    Verify(OverloadedMethod(clientFake, write, size_t(uint8_t)).Using(val2)).Once();
}

namespace ClientTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_basics);
        RUN_TEST(test_connect);
        RUN_TEST(test_write);
        RUN_TEST(test_read);
        RUN_TEST(test_inject_instance);
    }
}

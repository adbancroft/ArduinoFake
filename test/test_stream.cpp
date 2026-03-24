#include <Arduino.h>
#include "SimpleArduinoFake.h"
#include <unity.h>
#include "unity_filename_helper.h"

using namespace fakeit;

static void test_extends_print(void)
{
    auto &streamFake = SimpleArduinoFake::getContext()._Stream;
    auto &printFake = SimpleArduinoFake::getContext()._Print;

    char print_char_var = 'A';
    char stream_char_var = 'B';

    int print_int_var = 123;
    int stream_int_var = 321;

    When(OverloadedMethod(streamFake, print, size_t(char))).AlwaysReturn();
    When(OverloadedMethod(streamFake, print, size_t(int, int))).AlwaysReturn();

    When(OverloadedMethod(printFake, print, size_t(char))).AlwaysReturn();
    When(OverloadedMethod(printFake, print, size_t(int, int))).AlwaysReturn();

    Stream* pStream(streamFake.getFake());
    Print* pPrint(printFake.getFake());
    TEST_ASSERT_NOT_EQUAL(pStream, pPrint);

    pStream->print(stream_char_var);
    pStream->print(stream_int_var, DEC);

    pPrint->print(print_char_var);
    pPrint->print(print_int_var, DEC);

    Verify(OverloadedMethod(streamFake, print, size_t(char)).Using(stream_char_var)).Once();
    Verify(OverloadedMethod(streamFake, print, size_t(int, int)).Using(stream_int_var, DEC)).Once();

    Verify(OverloadedMethod(printFake, print, size_t(char)).Using(print_char_var)).Once();
    Verify(OverloadedMethod(printFake, print, size_t(int, int)).Using(print_int_var, DEC)).Once();
}

static void test_stream_basics(void)
{
    auto &streamFake = SimpleArduinoFake::getContext()._Stream;
    When(Method(streamFake, available)).Return(0, 1, 0);
    When(Method(streamFake, read)).Return(11, 12, 13);
    When(Method(streamFake, peek)).Return(21, 22, 23);
    When(Method(streamFake, flush)).AlwaysReturn();
    When(Method(streamFake, setTimeout)).AlwaysReturn();
    When(Method(streamFake, getTimeout)).AlwaysReturn(11);

    Stream* stream(streamFake.getFake());

    TEST_ASSERT_EQUAL(0, stream->available());
    TEST_ASSERT_EQUAL(1, stream->available());
    TEST_ASSERT_EQUAL(0, stream->available());

    TEST_ASSERT_EQUAL(11, stream->read());
    TEST_ASSERT_EQUAL(12, stream->read());
    TEST_ASSERT_EQUAL(13, stream->read());

    TEST_ASSERT_EQUAL(21, stream->peek());
    TEST_ASSERT_EQUAL(22, stream->peek());
    TEST_ASSERT_EQUAL(23, stream->peek());

    TEST_ASSERT_EQUAL(11, stream->getTimeout());

    stream->flush();
    stream->setTimeout(1L);
    
    Verify(Method(streamFake, available)).Exactly(3_Times);
    Verify(Method(streamFake, read)).Exactly(3_Times);
    Verify(Method(streamFake, peek)).Exactly(3_Times);
    Verify(Method(streamFake, flush)).Once();
    Verify(Method(streamFake, getTimeout)).Once();
    Verify(Method(streamFake, setTimeout)).Once();
}

static void test_stream_find(void)
{
    char char_val1 = 'A';
    char char_val2 = 'B';
    char terminator = '*';

    char* char_ptr1 = &char_val1;
    char* char_ptr2 = &char_val2;
    char* terminator_ptr = &terminator;

    auto &streamFake = SimpleArduinoFake::getContext()._Stream;
    When(OverloadedMethod(streamFake, find, bool(const char*))).Return(true, false);
    When(OverloadedMethod(streamFake, find, bool(const char*, size_t))).Return(true, false);

    When(OverloadedMethod(streamFake, findUntil, bool(const char*, const char*))).Return(true, false);
    When(OverloadedMethod(streamFake, findUntil, bool(const char*, size_t, const char*, size_t))).Return(true, false);

    Stream* stream(streamFake.getFake());

    TEST_ASSERT_EQUAL(true, stream->find(char_ptr1));
    TEST_ASSERT_EQUAL(false, stream->find(char_ptr2));

    TEST_ASSERT_EQUAL(true, stream->find(char_ptr1, 10));
    TEST_ASSERT_EQUAL(false, stream->find(char_ptr2, 20));

    TEST_ASSERT_EQUAL(true, stream->findUntil(char_ptr1, terminator_ptr));
    TEST_ASSERT_EQUAL(false, stream->findUntil(char_ptr2, terminator_ptr));

    TEST_ASSERT_EQUAL(true, stream->findUntil(char_ptr1, 10, terminator_ptr, 11));
    TEST_ASSERT_EQUAL(false, stream->findUntil(char_ptr2, 20, terminator_ptr, 21));

    Verify(OverloadedMethod(streamFake, find, bool(const char*)).Using(char_ptr1)).Once();
    Verify(OverloadedMethod(streamFake, find, bool(const char*)).Using(char_ptr2)).Once();

    Verify(OverloadedMethod(streamFake, find, bool(const char*, size_t)).Using(char_ptr1, 10)).Once();
    Verify(OverloadedMethod(streamFake, find, bool(const char*, size_t)).Using(char_ptr2, 20)).Once();

    Verify(OverloadedMethod(streamFake, findUntil, bool(const char*, const char*))).Exactly(2_Times);
    Verify(OverloadedMethod(streamFake, findUntil, bool(const char*, size_t, const char*, size_t))).Exactly(2_Times);
}

static void test_stream_parse(void)
{
    auto &streamFake = SimpleArduinoFake::getContext()._Stream;
    When(OverloadedMethod(streamFake, parseInt, long(LookaheadMode, char))).Return(10, 11);
    When(OverloadedMethod(streamFake, parseFloat, float(LookaheadMode, char))).Return(2.0, 2.1);

    Stream* stream(streamFake.getFake());

    TEST_ASSERT_INT_WITHIN(0, 10, stream->parseInt());
    TEST_ASSERT_INT_WITHIN(0, 11, stream->parseInt());

    TEST_ASSERT_FLOAT_WITHIN(0, 2.0, stream->parseFloat());
    TEST_ASSERT_FLOAT_WITHIN(0, 2.1, stream->parseFloat());

    Verify(OverloadedMethod(streamFake, parseInt, long(LookaheadMode, char))).Exactly(2_Times);
    Verify(OverloadedMethod(streamFake, parseFloat, float(LookaheadMode, char))).Exactly(2_Times);
}

static void test_stream_read(void)
{
    char char_val1 = 'A';
    char char_val2 = 'B';
    char terminator = '*';
    String str1 = String('X');
    String str2 = String('Z');

    char* char_ptr1 = &char_val1;
    char* char_ptr2 = &char_val2;

    auto &streamFake = SimpleArduinoFake::getContext()._Stream;
    When(OverloadedMethod(streamFake, readBytes, size_t(char *, size_t))).Return(1, 2);
    When(OverloadedMethod(streamFake, readBytesUntil, size_t(char, char*, size_t))).Return(3, 4);
    When(Method(streamFake, readString)).Return(str1, str2);
    When(Method(streamFake, readStringUntil)).Return(str1, str2);

    Stream* stream(streamFake.getFake());

    TEST_ASSERT_EQUAL_INT(1, stream->readBytes(char_ptr1, 10));
    TEST_ASSERT_EQUAL_INT(2, stream->readBytes(char_ptr2, 20));

    TEST_ASSERT_EQUAL_INT(3, stream->readBytesUntil(terminator, char_ptr1, 10));
    TEST_ASSERT_EQUAL_INT(4, stream->readBytesUntil(terminator, char_ptr2, 20));

    TEST_ASSERT_TRUE(str1.equals(stream->readString()));
    TEST_ASSERT_TRUE(str2.equals(stream->readString()));

    TEST_ASSERT_TRUE(str1.equals(stream->readStringUntil(terminator)));
    TEST_ASSERT_TRUE(str2.equals(stream->readStringUntil(terminator)));

    Verify(OverloadedMethod(streamFake, readBytes, size_t(char *, size_t)).Using(char_ptr1, 10)).Once();
    Verify(OverloadedMethod(streamFake, readBytes, size_t(char *, size_t)).Using(char_ptr2, 20)).Once();

    Verify(OverloadedMethod(streamFake, readBytesUntil, size_t(char, char*, size_t)).Using(terminator, char_ptr1, 10)).Once();
    Verify(OverloadedMethod(streamFake, readBytesUntil, size_t(char, char*, size_t)).Using(terminator, char_ptr2, 20)).Once();

    Verify(Method(streamFake, readString)).Exactly(2_Times);
    Verify(OverloadedMethod(streamFake, readBytesUntil, size_t(char, char*, size_t))).Exactly(2_Times);
}

namespace StreamTest
{
    void run_tests(void)
    {
        unity_filename_helper_t _ufname_helper(__FILE__);
        RUN_TEST(test_extends_print);
        RUN_TEST(test_stream_basics);
        RUN_TEST(test_stream_find);
        RUN_TEST(test_stream_parse);
        RUN_TEST(test_stream_read);
    }
}

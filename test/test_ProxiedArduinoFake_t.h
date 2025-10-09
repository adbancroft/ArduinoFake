#ifdef UNIT_TEST

namespace ProxiedArduinoFakeTTest
{
    struct IDummy
    {
        virtual void foo(void) { }
    };
    
    struct IArduino
    {
        virtual void bar(void) {}
    };

    struct IDummyProxy : public IArduino
    {
        IDummy *_dummy;
        IDummy* getFake(void) { return _dummy; }

        virtual void bar(void) override {}
    };

    void test_getFake(void)
    {
        ProxiedArduinoFake_t<IDummy, IDummyProxy> subject;

        IDummyProxy proxy;

        proxy._dummy = nullptr;
        TEST_ASSERT_EQUAL_PTR(nullptr, subject.getFake<IArduino>(&proxy));

        IDummy dummy;
        proxy._dummy = &dummy;
        TEST_ASSERT_EQUAL_PTR(&dummy, subject.getFake<IArduino>(&proxy));

        // Following should throw exception
        try
        {
            IArduino arduino;
            TEST_ASSERT_EQUAL_PTR(&dummy, subject.getFake<IArduino>(&arduino));
            TEST_FAIL();
        }
        catch(const std::runtime_error& e)
        {
        }
    }

    void run_tests(void)
    {
        RUN_TEST(test_getFake);
    }
}

#endif
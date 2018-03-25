#ifndef UT_BUTTON_H_VPZWRLC7
#define UT_BUTTON_H_VPZWRLC7

#include <CppUTest/TestHarness.h>
#include "button.h"
#include "Arduino.h"

TEST_GROUP(basic)
{
    void setup()
    {
        fixtures::registerInstance(f);
    }

    fixtures f;
};

TEST(basic, nothing)
{
};

TEST(basic, leak_prevent)
{
    button_t *b = new button_t(1);
    CHECK(b != NULL);
    delete b;
};

TEST_GROUP(initial_setup)
{
    void setup()
    {
        fixtures::registerInstance(f);
    }

    void teardown()
    {
        f.check();
    }

    fixtures f;
};

TEST(initial_setup, pin_mode)
{
    button_t b(1);
    f.set_expected_pin_mode(1, INPUT);
    f.set_expected_pin_mode(2, NOTSET);
    f.set_expected_call("pinMode", 1);
};

TEST(initial_setup, other_pin_mode)
{
    button_t b(2);
    f.set_expected_pin_mode(2, INPUT);
    f.set_expected_pin_mode(1, NOTSET);
    f.set_expected_call("pinMode", 1);
};

#endif /* end of include guard: UT_BUTTON_H_VPZWRLC7 */

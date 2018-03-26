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

static void single_click_stub(void *pcounter)
{
    int *counter = static_cast<int *>(pcounter);
    (*counter)++;
}

TEST_GROUP(single_click_button)
{
    void setup()
    {
        fixtures::registerInstance(f);
        f.set_millis(0);
        f.set_actual_digital_value(1, HIGH);

        expected_counter = 0;
        counter = 0;

        b = new button_t(1);
        b->on_single_click(single_click_stub, &counter);
    }

    void teardown()
    {
        f.check();

        delete b;

        LONGS_EQUAL(expected_counter, counter);
    }

    fixtures f;
    button_t *b;
    int counter;
    int expected_counter;
};

TEST(single_click_button, no_press)
{
    for (int i = 0; i < 10001; i+= 100) {
        f.set_micros(i);
        b->loop();
    }
}

TEST(single_click_button, one_click)
{
    b->loop();
    f.set_millis(100);
    f.set_actual_digital_value(1, LOW);
    b->loop();
    f.set_millis(200);
    f.set_actual_digital_value(1, HIGH);
    b->loop();
    f.set_millis(400);
    b->loop();
    f.set_millis(600);
    b->loop();

    expected_counter = 1;
}

TEST(single_click_button, long_click)
{
    b->loop();
    f.set_millis(100);
    f.set_actual_digital_value(1, LOW);
    b->loop();
    f.set_millis(2500);
    f.set_actual_digital_value(1, HIGH);
    b->loop();
    f.set_millis(2700);
    b->loop();
    f.set_millis(2900);
    b->loop();
}

TEST(single_click_button, double_click)
{
    b->loop();
    f.set_millis(100);
    f.set_actual_digital_value(1, LOW);
    b->loop();
    f.set_millis(200);
    f.set_actual_digital_value(1, HIGH);
    b->loop();
    f.set_millis(400);
    f.set_actual_digital_value(1, LOW);
    b->loop();
    f.set_millis(600);
    f.set_actual_digital_value(1, HIGH);
    b->loop();
    f.set_millis(800);
    b->loop();
    f.set_millis(1000);
    b->loop();
}

TEST(single_click_button, ten_click_every_seconds)
{
    b->loop();
    for (int i = 0; i < 10; i++) {
        f.set_millis(i * 1000 + 100);
        f.set_actual_digital_value(1, LOW);
        b->loop();
        f.set_millis(i * 1000 + 200);
        f.set_actual_digital_value(1, HIGH);
        b->loop();
        f.set_millis(i * 1000 + 400);
        b->loop();
        f.set_millis(i * 1000 + 600);
        b->loop();
        LONGS_EQUAL(i + 1, counter);
    }

    expected_counter = 10;
}


#endif /* end of include guard: UT_BUTTON_H_VPZWRLC7 */

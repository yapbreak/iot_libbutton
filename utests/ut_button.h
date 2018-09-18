#ifndef UT_BUTTON_H_VPZWRLC7
#define UT_BUTTON_H_VPZWRLC7

#include <CppUTest/TestHarness.h>
#include "button.h"
#include "ArduinoFixtures.h"

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

static void click_stub(void *pcounter)
{
    int *counter = static_cast<int *>(pcounter);
    (*counter)++;
}

TEST_GROUP(click_button)
{
    void setup()
    {
        fixtures::registerInstance(f);
        f.set_millis(0);
        f.set_actual_digital_value(1, HIGH);

        expected_single_counter = 0;
        single_counter = 0;
        expected_long_counter = 0;
        long_counter = 0;
        expected_double_counter = 0;
        double_counter = 0;

        b = new button_t(1);
        b->on_single_click(click_stub, &single_counter);
        b->on_long_click(click_stub, &long_counter);
        b->on_double_click(click_stub, &double_counter);
    }

    void teardown()
    {
        f.check();

        delete b;

        LONGS_EQUAL(expected_single_counter, single_counter);
        LONGS_EQUAL(expected_long_counter, long_counter);
        LONGS_EQUAL(expected_double_counter, double_counter);
    }

    fixtures f;
    button_t *b;
    int long_counter;
    int single_counter;
    int double_counter;
    int expected_long_counter;
    int expected_single_counter;
    int expected_double_counter;
};

TEST(click_button, no_press)
{
    for (int i = 0; i < 10001; i+= 100) {
        f.set_micros(i);
        b->loop();
    }
}

TEST(click_button, one_click)
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

    expected_single_counter = 1;
}

TEST(click_button, long_click)
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

    expected_long_counter = 1;
}

TEST(click_button, double_click)
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

    expected_double_counter = 1;
}

TEST(click_button, ten_click_every_seconds)
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
        LONGS_EQUAL(i + 1, single_counter);
    }

    expected_single_counter = 10;
}

TEST(click_button, ten_long_click_every_ten_seconds)
{
    b->loop();
    for (int i = 0; i < 10; i++) {
        f.set_millis(i * 10000 + 100);
        f.set_actual_digital_value(1, LOW);
        b->loop();
        f.set_millis(i * 10000 + 2500);
        f.set_actual_digital_value(1, HIGH);
        b->loop();
        f.set_millis(i * 10000 + 4000);
        b->loop();
        f.set_millis(i * 10000 + 6000);
        b->loop();
        LONGS_EQUAL(i + 1, long_counter);
    }

    expected_long_counter = 10;
}

TEST(click_button, ten_double_click_every_second)
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
        f.set_actual_digital_value(1, LOW);
        b->loop();
        f.set_millis(i * 1000 + 600);
        f.set_actual_digital_value(1, HIGH);
        b->loop();
        f.set_millis(i * 1000 + 800);
        b->loop();
        f.set_millis(i * 1000 + 1000);
        b->loop();
        LONGS_EQUAL(i + 1, double_counter);
    }

    expected_double_counter = 10;
}

#endif /* end of include guard: UT_BUTTON_H_VPZWRLC7 */

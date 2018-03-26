#include <Arduino.h>

#include "button.h"

// Create a button connected to pin 4.
button_t my_button(4);

void click(void *arg)
{
    Serial.println("Click");
}

void doubleclick(void *arg)
{
    Serial.println("Double click");
}

void setup() {
    Serial.begin(115200);

    my_button.on_single_click(click, NULL);
    my_button.on_double_click(doubleclick, NULL);
    my_button.on_long_click([&](void *arg) {
          Serial.println("Long click");
      }, NULL);
}

void loop() {
    my_button.loop();
}

#ifndef ARDUINO
int main(int argc, char *argv)
{
    (void) argc;
    (void) argv;

    setup();

    for (;;)
        loop();

    return 0;
}
#endif

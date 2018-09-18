#include <Arduino.h>

#include "button.h"

// Create a button connected to pin 4.
button_t my_button(4);

/**
 * @brief Callback for a single click.
 *
 * @param arg (UNUSED)
 */
void click(void *arg)
{
    (void) arg;
    Serial.println("Click");
}

/**
* @brief Callback for a double click.
*
* @param arg (UNUSED)
*/
void doubleclick(void *arg)
{
    (void) arg;
    Serial.println("Double click");
}

/**
* @brief Callback for a long click.
*
* @param arg (UNUSED)
*/
void longclick(void *arg)
{
    (void) arg;
    Serial.println("Long click");
}

/**
* @brief Arduino function to setup and initialize everything.
*/
extern "C" void setup() {
    Serial.begin(115200);

    my_button.on_single_click(click, NULL);
    my_button.on_double_click(doubleclick, NULL);
    my_button.on_long_click(longclick, NULL);
}

/**
* @brief Arduino function called in the main loop.
*/
extern "C" void loop() {
    my_button.loop();
}

/**
 * @file simple.cpp
 * @brief Simple click with a button connected to PIN 4.
 */

/// [Click]
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
    Serial.println("Click");
}

/**
* @brief Callback for a double click.
*
* @param arg (UNUSED)
*/
void doubleclick(void *arg)
{
    Serial.println("Double click");
}

/**
* @brief Arduino function to setup and initialize everything.
*/
// cppcheck-suppress unusedFunction
extern "C" void setup() {
    Serial.begin(115200);

    my_button.on_single_click(click, NULL);
    my_button.on_double_click(doubleclick, NULL);
    my_button.on_long_click([&](void *arg) {
          Serial.println("Long click");
      }, NULL);
}

/**
* @brief Arduino function called in the main loop.
*/
extern "C" void loop() {
    my_button.loop();
}
/// [Click]

/**
 * @file button.h
 * @author Adrien Oliva <olivaa+gitlab@yapbreak.fr>
 * @date 2018-03-27
 * @brief Main classes definitions.
 *
 * @section main API description and purpose
 *
 * @subsection ex_simple Simple Button Click Sample
 * @snippet simple.cpp Click
 */
/*         DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                Version 2, December 2004
 *
 * Copyright 2017 Adrien Oliva <olivaa+gitlab@yapbreak.fr>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *        DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 */

/**
 * @mainpage LibButton
 *
 * This is a small IOT library to easily handle buttons.
 */
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <functional>

/**
* @brief Generic click callback function.
*
* User defined callback called on every click (single, double or long).
*/
typedef std::function<void(void *)> button_callback_t;

/**
* @brief Abstract a button.
*
* This is the main button interface. Given a GPIO pin, you can set callbacks
* that react on single click, double click or long click.
*/
class button_t {
    private:
        /**
        * @brief A PIN identifier where button is connected.
        */
        const uint8_t m_pin;

        /**
        * @brief Store last button state seen.
        */
        bool m_last_down = false;
        /**
        * @brief Store time for next relevent event.
        */
        unsigned long m_next_event_time = 0;
        /**
        * @brief Store keypress time.
        */
        unsigned long m_keypress_time = 0;
        /**
        * @brief Number of event appears within given time.
        */
        char m_event_count = 0;
        /**
        * @brief Long press flag.
        */
        bool m_long_enable = false;

        /**
        * @brief Single click callback registration slot.
        */
        button_callback_t m_single_click_callback = NULL;
        /**
        * @brief Double click callback registration slot.
        */
        button_callback_t m_double_click_callback = NULL;
        /**
        * @brief Long click callback registration slot.
        */
        button_callback_t m_long_click_callback = NULL;

        /**
        * @brief User defined argument for single click callback
        */
        void *m_single_arg = NULL;
        /**
        * @brief User defined argument for double click callback
        */
        void *m_double_arg = NULL;
        /**
        * @brief User defined argument for long click callback
        */
        void *m_long_arg = NULL;

    public:
        /**
        * @brief Main button constructor.
        *
        * @param pin GPIO connected to the button controlled by this interface.
        */
        explicit button_t(const uint8_t pin);
        /**
        * @brief Default destructor.
        */
        ~button_t();

        /**
        * @brief Set single click callback.
        *
        * @param callback Function called upon single click.
        * @param arg Argument passed to callback function.
        *
        * A single click is caracterized by a press shorter than 2 seconds,
        * followed by a release for more than 250 ms.
        */
        void on_single_click(const button_callback_t &callback, void *arg);
        /**
        * @brief Set double click callback.
        *
        * @param callback Function called upon double click.
        * @param arg Argument passed to callback function.
        *
        * A double click is characterized by a press shorter than 2 seconds,
        * followed by another press shorter than 2 seconds in less than
        * 250 ms interval.
        */
        void on_double_click(const button_callback_t &callback, void *arg);
        /**
        * @brief Set long click callback.
        *
        * @param callback Function called upon single click.
        * @param arg Argument passed to callback function.
        *
        * A long click is characterized by a press longer than 2 seconds.
        */
        void on_long_click(const button_callback_t &callback, void *arg);

        /**
        * @brief Main loop function, to be called in Arduino's loop function.
        */
        void loop();
};

#endif /* __BUTTON_H__ */

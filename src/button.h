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
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <functional>

typedef std::function<void(void *)> button_callback_t;

class button_t {
    private:
        const uint8_t m_pin;

        bool m_last_down = false;
        unsigned long m_next_event_time = 0;
        unsigned long m_keypress_time = 0;
        char m_event_count = 0;
        bool m_long_enable = false;

        button_callback_t m_single_click_callback = NULL;
        button_callback_t m_double_click_callback = NULL;
        button_callback_t m_long_click_callback = NULL;

        void *m_single_arg = NULL;
        void *m_double_arg = NULL;
        void *m_long_arg = NULL;

    public:
        button_t(const uint8_t pin);
        ~button_t();

        void on_single_click(button_callback_t callback, void *arg);
        void on_double_click(button_callback_t callback, void *arg);
        void on_long_click(button_callback_t callback, void *arg);

        void loop();
};

#endif /* __BUTTON_H__ */

#include <Arduino.h>

#include "button.h"

#define DOUBLECLICK_TIMER   250
#define LONGCLICK_TIMER 2000

button_t::button_t(const uint8_t pin)
    : m_pin(pin)
{
    pinMode(m_pin, INPUT);
}

button_t::~button_t()
{

}

void button_t::on_single_click(button_callback_t callback, void *arg)
{
    m_single_click_callback = callback;
    m_single_arg = arg;
}

void button_t::on_double_click(button_callback_t callback, void *arg)
{
    m_double_click_callback = callback;
    m_double_arg = arg;
}

void button_t::on_long_click(button_callback_t callback, void *arg)
{
    m_long_click_callback = callback;
    m_long_arg = arg;
}

void button_t::loop()
{
    int current_state = digitalRead(m_pin);
    unsigned long t = millis();

    if (!m_last_down && (current_state == LOW)) {
        m_keypress_time = t + LONGCLICK_TIMER;
        m_long_enable = true;
    }

    if (m_last_down && current_state) {
      if (m_long_enable && m_keypress_time <  t) {
        if (m_long_click_callback)
          m_long_click_callback(m_long_arg);
      } else {
        m_event_count++;
        m_next_event_time = t + DOUBLECLICK_TIMER;
      }
      m_long_enable = false;
    } else if (m_event_count != 0) {
        if (m_next_event_time < t) {
            switch (m_event_count) {
                case 1:
                    if (m_single_click_callback)
                        m_single_click_callback(m_single_arg);
                    break;
                case 2:
                    if (m_double_click_callback)
                        m_double_click_callback(m_double_arg);
                    break;
            }
            m_event_count = 0;
        }
    }

    m_last_down = (current_state == LOW);

}

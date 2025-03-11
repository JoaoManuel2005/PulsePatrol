#ifndef PP_SWITCH_HPP
#define PP_SWITCH_HPP

#define PP_SWITCH_IN p15

#include "mbed.h"

enum SwitchState
{
    OFF, 
    ON,
};

class Switch
{
    private:
        InterruptIn m_sw;
        uint64_t m_lastDebounceTime;
        uint16_t m_debounceDelay = 2000;
        volatile SwitchState m_state;
        Timer* m_timer;

        void handleInterrupt();
    public:
        Switch(Timer& timer);
        SwitchState read();
};

#endif // PP_SWITCH_HPP
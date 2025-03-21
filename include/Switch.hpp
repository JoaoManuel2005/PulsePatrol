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
        uint32_t m_lastDebounceTime;
        const uint32_t m_debounceDelay = 50;
        volatile SwitchState m_state;
        Timer m_timer;
        bool debounceFlag = false;

        void handleInterrupt();
    public:
        Switch();
        SwitchState read();
};

#endif // PP_SWITCH_HPP
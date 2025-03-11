#include "Switch.hpp"

Switch::Switch(Timer& timer) : m_sw(PP_SWITCH_IN), m_state(OFF), m_timer(&timer) 
{
    m_sw.fall(callback(this, &Switch::handleInterrupt));
    m_sw.rise(callback(this, &Switch::handleInterrupt));
}


void Switch::handleInterrupt()
{
    uint64_t now = chrono::duration_cast<chrono::microseconds>(m_timer->elapsed_time()).count();
    if (now - m_lastDebounceTime > m_debounceDelay)
    {
        m_lastDebounceTime = now;
        m_state = (m_sw.read()) ? ON : OFF;
    }
    // uint64_t m_lastDebounceTime = chrono::duration_cast<chrono::microseconds>(m_timer->elapsed_time()).count();
}

SwitchState Switch::read()
{
    return m_state; 
}

// SwitchState Switch::read()
// {
//     if (m_sw != m_state)
//     {

//     }
//     if (chrono::duration_cast<chrono::microseconds>(m_timer->elapsed_time()).count() - m_lastDebounceTime > m_debounceDelay)
//     {
//         if (m_sw != m_state)
//         {
//             m_prevSw = m_sw;
//         }
//     }

//     if (m_prevSw)
//     {
//         return SwitchState::ON;
//     }
//     return SwitchState::OFF;
// }
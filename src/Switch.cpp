#include "Switch.hpp"

/**
 * @brief Switch constructor.
 * Initialises InterruptIn pin, initialises state to OFF
 * Assigns handleInterrupt function as interrupt callback on switch rise or fall
*/
Switch::Switch() : m_sw(PP_SWITCH_IN), m_state(SwitchState::OFF), m_lastDebounceTime(0)
{
    m_timer.start();
    m_sw.fall(callback(this, &Switch::handleInterrupt));
    m_sw.rise(callback(this, &Switch::handleInterrupt));
}

/**
 * @brief Interrupt callback that gets called on switch rise or fall.
 * Debounces switch input using timer + flag approach
 * 
*/
void Switch::handleInterrupt()
{
    int reading = m_sw.read();

    if (reading != m_state && !debounceFlag)
    {
        debounceFlag = true;
        m_lastDebounceTime = chrono::duration_cast<chrono::milliseconds>(m_timer.elapsed_time()).count();
    }

    uint32_t now = chrono::duration_cast<chrono::milliseconds>(m_timer.elapsed_time()).count();
    if ((now - m_lastDebounceTime > m_debounceDelay) && debounceFlag)
    {
        if (reading != m_state)
        {
            m_state = reading ? SwitchState::ON : SwitchState::OFF;
            debounceFlag = false;
        }        
    }
}

/**
 * @return current state of the switch
*/
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
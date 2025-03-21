#include "Sensor.hpp"

/**
 * Digitises analogue input signal
*/
void Sensor::read()
{
    y = ADC.read_u16();
}

/**
 * Getter for digitsed sensor signal
*/
uint16_t Sensor::getY()
{
    return y;
}
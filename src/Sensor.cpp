#include "Sensor.hpp"

void Sensor::read()
{
    y = ADC.read_u16();
}

const uint16_t Sensor::getY()
{
    return y;
}
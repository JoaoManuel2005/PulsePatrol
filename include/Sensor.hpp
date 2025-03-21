#ifndef PP_SENSOR_HPP
#define PP_SENSOR_HPP

#include "mbed.h"

#define PP_SENSOR_IN p17

class Sensor
{
    private:
        AnalogIn ADC = AnalogIn(PP_SENSOR_IN); // Analogue signal input from sensor
        uint16_t y; // Digitised input signal

    public:
        void read();
        uint16_t getY();
};

#endif // PP_SENSOR_HPP
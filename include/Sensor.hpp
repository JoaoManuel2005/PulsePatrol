#ifndef PP_SENSOR_HPP
#define PP_SENSOR_HPP

#include "mbed.h"

#define PP_SENSOR_IN p17

class Sensor
{
    private:
        AnalogIn ADC = AnalogIn(PP_SENSOR_IN);
        uint16_t y;

    public:
        void read();
        const uint16_t getY();
};

#endif // PP_SENSOR_HPP
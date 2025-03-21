#include "compFilter.hpp"

/**
 * @brief Runs complementary filter on new sensor data.
 * Updates moving average with new sensor data
 * @param x digitised sensor signal
*/
void compFilter::update(const float& x)
{
    y = alpha * x + (1 - alpha) * y;

    movingAvgSum -= movingAvgBuffer[bufferIndex];
    movingAvgBuffer[bufferIndex] = y;      
    movingAvgSum += y;                     
    bufferIndex = (bufferIndex + 1) % MOVING_AVG_WINDOW;

    movingAvg = movingAvgSum / MOVING_AVG_WINDOW;
}

/**
 * Getter for filtered digitised sensor signal
*/
float compFilter::getY()
{
    return y;
}

/**
 * Getter for filtered moving average
*/
float compFilter::getMovingAverage()
{
    return movingAvg;
}

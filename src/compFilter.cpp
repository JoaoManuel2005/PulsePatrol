#include "compFilter.hpp"


void compFilter::update(const float& x)
{
    y = alpha * x + (1 - alpha) * y;

    movingAvgSum -= movingAvgBuffer[bufferIndex];
    movingAvgBuffer[bufferIndex] = y;      
    movingAvgSum += y;                     
    bufferIndex = (bufferIndex + 1) % MOVING_AVG_WINDOW;

    movingAvg = movingAvgSum / MOVING_AVG_WINDOW;
}

const float compFilter::getY()
{
    return y;
}

const float compFilter::getMovingAverage()
{
    return movingAvg;
}

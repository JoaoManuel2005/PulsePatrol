#include "compFilter.hpp"


void compFilter::update(const float& x)
{
    y = alpha * x + (1 - alpha) * y;
}

const float compFilter::getY()
{
    return y;
}

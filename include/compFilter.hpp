#ifndef COMP_FILTER_HPP
#define COMP_FILTER_HPP

#define MOVING_AVG_WINDOW 1000

class compFilter
{
    private:
        float alpha = 0.50;
        float y = 0;
        int bufferIndex = 0;
        float movingAvgBuffer[MOVING_AVG_WINDOW] = {0}; 
        float movingAvgSum = 0;
        float movingAvg = 0;

    public:
        void update(const float& x);
        const float getY();
        const float getMovingAverage();

};

#endif // COMP_FILTER_HPP
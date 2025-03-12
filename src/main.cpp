#include "mbed.h"
#include "platform/mbed_thread.h"
#include <memory.h>

#include "compFilter.hpp"
#include "Sensor.hpp"
#include "LCD.hpp"

const float PEAK_THRESHOLD = 1000;
const float LOW_THRESHOLD = 500;
const int MAX_BPM_SAMPLES = 5;

bool peakDetected = false;
float lastPeakTime = 0;
float beatIntervals[MAX_BPM_SAMPLES] = {0};
int beatIndex = 0;

int main()
{
    Sensor heartBeatSensor;
    compFilter filter;
    Timer timer;
    DigitalOut led(LED1);
    LCD lcd;

    timer.start();
    int bpm = 0;

    while(1)
    {
        heartBeatSensor.read();
        filter.update(heartBeatSensor.getY());
        float y = filter.getY();
        float baseline = filter.getMovingAverage();

        if ((y > baseline + PEAK_THRESHOLD) && !peakDetected)
        {
            peakDetected = true;
            led = 1;

            float currentTime = timer.read();
            float interval = currentTime - lastPeakTime;
            lastPeakTime = currentTime;

            if (beatIndex < MAX_BPM_SAMPLES) {
                beatIntervals[beatIndex] = interval;
                beatIndex++;
            } else {
                // Shift buffer for new values
                for (int i = 0; i < MAX_BPM_SAMPLES - 1; i++) {
                    beatIntervals[i] = beatIntervals[i + 1];
                }
                beatIntervals[MAX_BPM_SAMPLES - 1] = interval;
            }

            // Compute average interval and BPM
            float avgInterval = 0;
            for (int i = 0; i < beatIndex; i++) {
                avgInterval += beatIntervals[i];
            }
            avgInterval /= beatIndex;

            bpm = (int)(60.0 / avgInterval);
            lcd.write(bpm);
        }

        if (y < baseline + LOW_THRESHOLD) 
        {
            peakDetected = false;
            led = 0; 
        }

        ThisThread::sleep_for(10ms);
    }
}
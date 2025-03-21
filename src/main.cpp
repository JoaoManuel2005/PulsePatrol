#include "mbed.h"
#include "platform/mbed_thread.h"
#include <memory.h>

#include <chrono>

#include "compFilter.hpp"
#include "Sensor.hpp"
#include "LCD.hpp"
#include "LedMatrix.hpp"
#include "PPThreads.hpp"
#include "Switch.hpp"

const float PEAK_THRESHOLD = 1000;
const float LOW_THRESHOLD = 500;
const int MAX_BPM_SAMPLES = 500;

AnalogOut Aout(p18);

bool peakDetected = false;
float lastPeakTime = 0;
float beatIntervals[MAX_BPM_SAMPLES] = {0};
int beatIndex = 0;

/**
 * @brief Main BPM calculation logic
 * Heart beat sensor object reads analogue input voltage, digitises it
 * Complementary filter filters the digitised signal, and keeps a moving average of the signal
 * If the digitised signal > moving average + a peak threshold then we say we had a peak
 * We keep track of the last 500 periods between peaks and calculate the average period between peaks
 * Then: BPM = 60 / average period between peaks in seconds
*/
int main()
{
    Sensor heartBeatSensor;
    compFilter filter;
    Timer timer;
    DigitalOut led(LED2);

    ledMatrix.setup_dot_matrix();
    ledThread.start(led_display_task);

    lcdThread.start(lcd_display_task);

    timer.start();

    swThread.start(switch_task);

    while(1)
    {
        heartBeatSensor.read();
        filter.update(heartBeatSensor.getY());

        float y = filter.getY();
        float baseline = filter.getMovingAverage();
        Aout.write_u16(static_cast<unsigned short>(y));

        if ((y > baseline + PEAK_THRESHOLD) && !peakDetected)
        {
            peakDetected = true;
            led = 1;

            int currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer.elapsed_time()).count();

            float interval = currentTime - lastPeakTime;
            lastPeakTime = currentTime;

            if (beatIndex < MAX_BPM_SAMPLES) {
                beatIntervals[beatIndex] = interval;
                beatIndex++;
            } else {
                for (int i = 0; i < MAX_BPM_SAMPLES - 1; i++) {
                    beatIntervals[i] = beatIntervals[i + 1];
                }
                beatIntervals[MAX_BPM_SAMPLES - 1] = interval;
            }
            int avgInterval = 0;

            for (int i = 0; i < beatIndex; i++) {
                avgInterval += beatIntervals[i];
            }
            int avg = avgInterval / beatIndex;

            bpmMutex.trylock();
            if (avg > 0) {
                bpm = 60000 / avg;
            } else {
                bpm = 60; 
            }
            bpmMutex.unlock();
        }

        if (y < baseline + LOW_THRESHOLD) 
        {
            peakDetected = false;
            led = 0; 
        }

        ThisThread::sleep_for(10ms);
    }
}
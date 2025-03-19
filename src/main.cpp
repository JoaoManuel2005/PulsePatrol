#include "mbed.h"
#include "platform/mbed_thread.h"
#include <memory.h>

#include <chrono>

#include "compFilter.hpp"
#include "Sensor.hpp"
#include "LCD.hpp"
#include "LedMatrix.hpp"
#include "PPThreads.hpp"

const float PEAK_THRESHOLD = 1000;
const float LOW_THRESHOLD = 500;
const int MAX_BPM_SAMPLES = 500;
// const int MAX_PEAKS_SAMPLES = 50;

AnalogOut Aout(p18);

bool peakDetected = false;
float lastPeakTime = 0;
float beatIntervals[MAX_BPM_SAMPLES] = {0};
int beatIndex = 0;

// float peaks[MAX_PEAKS_SAMPLES];  

BufferedSerial pc(USBTX, USBRX, 115200);

Mutex serialMutex;

int main()
{
    Sensor heartBeatSensor;
    compFilter filter;
    Timer timer;
    DigitalOut led(LED1);

    ledMatrix.setup_dot_matrix();
    ledThread.start(led_display_task);

    lcdThread.start(lcd_display_task);

    timer.start();

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
                // Shift buffer for new values
                for (int i = 0; i < MAX_BPM_SAMPLES - 1; i++) {
                    beatIntervals[i] = beatIntervals[i + 1];
                }
                beatIntervals[MAX_BPM_SAMPLES - 1] = interval;
            }
            // Compute average interval and BPM
            int avgInterval = 0;

            for (int i = 0; i < beatIndex; i++) {
                avgInterval += beatIntervals[i];
            }
            // avgInterval /= beatIndex;
            int avg = avgInterval / beatIndex;

            bpmMutex.trylock();
            if (avg > 0) {
                bpm = 60000 / avg;
            } else {
                bpm = 60; // Default to a safe value
            }
            bpmMutex.unlock();

            // serialMutex.trylock();
            // char buffer[64];
            // snprintf(buffer, sizeof(buffer) - 1, "avg %d \n", avg);
            // buffer[sizeof(buffer) - 1] = '\0'; // Ensure null termination
            // pc.write(buffer, strlen(buffer)); // Use strlen instead of sizeof
            // serialMutex.unlock();

        }

        if (y < baseline + LOW_THRESHOLD) 
        {
            peakDetected = false;
            led = 0; 
        }
        ThisThread::sleep_for(10ms);
    }
}
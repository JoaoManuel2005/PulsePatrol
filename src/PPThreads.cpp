#include "PPThreads.hpp"

Thread ledThread;
Thread lcdThread;
Mutex bpmMutex;
volatile int bpm = 60;

LedMatrix ledMatrix;
LCD lcd;

void led_display_task()
{
    while (true)
    {
        bpmMutex.trylock();
        int currentBPM = bpm;
        bpmMutex.unlock();

        ledMatrix.display(currentBPM);
    }
}

void lcd_display_task()
{
    while (true)
    {
        bpmMutex.trylock();
        int currentBPM = bpm;
        bpmMutex.unlock();

        lcd.write(currentBPM);
        ThisThread::sleep_for(100ms);
    }
}
#include "PPThreads.hpp"

Thread ledThread;
Thread lcdThread;
Thread swThread;
Mutex bpmMutex;
volatile int bpm = 60;

LedMatrix ledMatrix;
LCD lcd;
Switch sw;
DigitalOut led_one(LED1);

/**
 * Task that LED Matrix thread runs
 * 
 * Displays heart on LED matrix that pulses at current BPM
*/
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

/**
 * Task that LCD thread runs
 * 
 * Displays current BPM on LCD
 * Refreshes at 10 Hz
*/
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

/**
 * Task that LED thread runs
 * 
 * Pulses the LPC1768's LED1 at the current BPM when the switch is on
*/
void switch_task()
{
    while (true)
    {
        if (sw.read())
        {
            bpmMutex.trylock();
            int currentBPM = bpm;
            bpmMutex.unlock();

            int delay_ms = 60000 / currentBPM;
            led_one = 1;
            ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 
            led_one = 0;
            ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 
        }
    }
}
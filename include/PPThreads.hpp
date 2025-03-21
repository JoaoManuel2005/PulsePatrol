#ifndef PP_THREADS_HPP
#define PP_THREADS_HPP

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "LCD.hpp"
#include "LedMatrix.hpp"
#include "Switch.hpp"

/**
 * Global threads, mutexes and variables
*/
extern Thread ledThread;
extern Thread lcdThread;
extern Thread swThread;
extern Mutex bpmMutex;
extern volatile int bpm;
extern LedMatrix ledMatrix;
extern LCD lcd;
extern Switch sw;
extern DigitalOut led_one;

void led_display_task();
void lcd_display_task();
void switch_task();

#endif // PP_THREADS_HPP
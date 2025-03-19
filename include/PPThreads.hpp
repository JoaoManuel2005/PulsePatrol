#ifndef PP_THREADS_HPP
#define PP_THREADS_HPP

#include "mbed.h"
#include "platform/mbed_thread.h"
#include "LCD.hpp"
#include "LedMatrix.hpp"

extern Thread ledThread;
extern Thread lcdThread;
extern Mutex bpmMutex;
extern volatile int bpm;

extern LedMatrix ledMatrix;
extern LCD lcd;

void led_display_task();
void lcd_display_task();

#endif // PP_THREADS_HPP
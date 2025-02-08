/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "TextLCD.h"
#include "platform/mbed_thread.h"


AnalogIn Ain(p17);
AnalogOut Aout(p18);

TextLCD lcd(p26, p25, p24, p23, p22, p21, TextLCD::LCD16x2);


int main()
{

    Ain.set_reference_voltage(5.0);
    while (1)
    {
        // unsigned short voltage = Ain.read_u16();
        // if (voltage > 0xFA00)
        // {
        //     Aout = 1;
        // }
        // else if (voltage > 0xEA60)
        // {
        //     Aout = 0.875;
        // }
        // else if (voltage > 0xDAC0)
        // {
        //     Aout = 0.750;
        // }
        // else if (voltage > 0xCB20)
        // {
        //     Aout = 0.625;
        // }
        // else if (voltage > 0xBB80)
        // {
        //     Aout = 0.5;
        // }
        // else if (voltage > 0xABE0)
        // {
        //     Aout = 0.375;
        // }
        // else if (voltage > 0x9C40)
        // {
        //     Aout = 0.25;
        // }
        // else if (voltage > 0x8CA0)
        // {
        //     Aout = 0.125;
        // }
        // else 
        // {
        //     Aout = 0;
        // }

        float voltage = Ain.read();
        if (voltage == 0)
        {
            Aout = 0;
        }
        else if (voltage < 0.125)
        {
            Aout = 0.125;
        }
        else if (voltage < 0.25)
        {
            Aout = 0.25;
        }
        else if (voltage < 0.375)
        {
            Aout = 0.375;
        }
        else if (voltage < 0.5)
        {
            Aout = 0.5;
        }
        else if (voltage < 0.625)
        {
            Aout = 0.635;
        }
        else if (voltage < 0.75)
        {
            Aout = 0.75;
        }
        else if (voltage < 0.875)
        {
            Aout = 0.875;
        }
        else
        {
            Aout = 1;
        }

        // unsigned short voltage = Ain.read_u16();
        // Aout.write_u16(voltage);

        lcd.setAddress(0,0);
        lcd.printf("%d", voltage);
    }

}

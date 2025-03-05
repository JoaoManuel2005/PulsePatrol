#ifndef PP_LCD_HPP
#define PP_LCD_HPP

#include <TextLCD.h>

#define PP_LCD_RS p26
#define PP_LCD_EN p25
#define PP_LCD_D4 p24
#define PP_LCD_D5 p23
#define PP_LCD_D6 p22
#define PP_LCD_D7 p21
#define PP_LCD_TYPE TextLCD::LCD16x2

class LCD
{
    private:
        TextLCD lcd;
        int m_prevReading;
    public:
        LCD();
        void write(int pulse);
};

#endif // PP_LCD_HPP
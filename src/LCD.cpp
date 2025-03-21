#include "LCD.hpp"

LCD::LCD() : lcd(PP_LCD_RS, PP_LCD_EN, PP_LCD_D4, PP_LCD_D5, PP_LCD_D6, PP_LCD_D7), m_prevReading(0) {}

/**
 * @brief Writes current BPM to LCD
 * @param pulse current BPM
*/
void LCD::write(int pulse)
{
    if (pulse != m_prevReading)
    {
        lcd.setAddress(0,0);
        lcd.printf("Pulse rate %d", pulse);
        m_prevReading = pulse;
    }
}

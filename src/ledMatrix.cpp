#include "LedMatrix.hpp"
#include "Config.hpp"

LedMatrix::LedMatrix() : max_spi(p5, NC, p7), spiLoad(p8) {}

/**
 * Displays a heart on the LED matrix that pulses at the BPM rate
*/
void LedMatrix::display(int bpm)
{
    if (bpm <= 0) return; 

    int delay_ms = 60000 / bpm; 

    pattern_to_display(pattern_heart);
    ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 

    clear();
    ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 
}

/**
 * @brief Initiates SPI comm by bring CS low.
 * Then we specify the register we want to write to. 
 * Then we write the actual data and end the SPI by bringing CS high.
*/
void LedMatrix::write_to_max(int reg, int col)
{
    spiLoad = LOW;
    max_spi.write(reg);
    max_spi.write(col); 
    spiLoad = HIGH;
}

/**
 * @brief Displays a pattern on the LED matrix
 * Loops through the patter array and writes it to the MAX
*/
void LedMatrix:: pattern_to_display(char *pattern)
{
    int cdata; 

    for (int idx = 0; idx <= 7; idx++) 
    {
        cdata = pattern[idx]; 
        write_to_max(idx+1, cdata);
    }
} 

/**
 * @brief Setups the LED matrix
 * Sets SPI up in mode 0, 8 bits
 * Sets the frequency to 100kHz
 * Configure the MAX to LED Matrix mode
 * Clear the LED Matrix by clearing all registers
*/
void LedMatrix::setup_dot_matrix()
{
    max_spi.format(8, 0);
    max_spi.frequency(100000);
    
    write_to_max(max7219_reg_scanLimit, 0x07);
    write_to_max(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
    write_to_max(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    write_to_max(max7219_reg_displayTest, 0x00); // no display test

    for (int e=1; e<=8; e++) 
    {   
        write_to_max(e,0);
    }

    write_to_max(max7219_reg_intensity,  0x08);     
}

/**
 * @brief Clear LED Matrix by clearing all registers
*/
void LedMatrix::clear()
{
    for (int e=1; e<=8; e++) 
    {    
        write_to_max(e,0); 
    }
}
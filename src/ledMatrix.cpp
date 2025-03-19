#include "LedMatrix.hpp"
#include "Config.hpp"


// LedMatrix::LedMatrix() : spi(SPI_MAX_MOSI, NC, SPI_MAX_LOAD), spiLoad(SPI_MAX_LOAD) {}

LedMatrix::LedMatrix() : max_spi(p5, NC, p7), spiLoad(p8) {}


void LedMatrix::display(int bpm)
{
    if (bpm <= 0) return; // Prevent divide-by-zero error

    int delay_ms = 60000 / bpm;  // Convert BPM to milliseconds per beat

    pattern_to_display(pattern_heart);
    ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 

    clear();
    ThisThread::sleep_for(std::chrono::milliseconds(delay_ms)); 
}

void LedMatrix::write_to_max(int reg, int col)
{
    spiLoad = LOW;  // initiate SPI comm by bringing CS low
    max_spi.write(reg); // sepcify register
    max_spi.write(col); // write data
    spiLoad = HIGH; // end SPI comm by bringing CS high
}

void LedMatrix:: pattern_to_display(char *pattern)
{
    int cdata; 

    for (int idx = 0; idx <= 7; idx++) 
    {
        cdata = pattern[idx]; 
        write_to_max(idx+1, cdata);
    }
} 

void LedMatrix::setup_dot_matrix()
{
    // initiation of the max 7219
    // SPI setup: 8 bits, mode 0
    max_spi.format(8, 0);
    max_spi.frequency(100000); //down to 100khx easier to scope ;-)
    
    write_to_max(max7219_reg_scanLimit, 0x07);
    write_to_max(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
    write_to_max(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    write_to_max(max7219_reg_displayTest, 0x00); // no display test

    for (int e=1; e<=8; e++) 
    {   
        write_to_max(e,0);  // empty registers, turn all LEDs off
    }

    write_to_max(max7219_reg_intensity,  0x08);     
}

void LedMatrix::clear()
{
    for (int e=1; e<=8; e++) 
    {    
        write_to_max(e,0); // empty registers, turn all LEDs off
    }
}
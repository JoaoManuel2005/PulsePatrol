#ifndef PP_LED_MATRIX_HPP
#define PP_LED_MATRIX_HPP

#include "mbed.h"

// const int SPI_MAX_MOSI = p5;
// #define SPI_MAX_SCK p7
// #define SPI_MAX_LOAD p8

#define max7219_reg_noop         0x00
#define max7219_reg_digit0       0x01
#define max7219_reg_digit1       0x02
#define max7219_reg_digit2       0x03
#define max7219_reg_digit3       0x04
#define max7219_reg_digit4       0x05
#define max7219_reg_digit5       0x06
#define max7219_reg_digit6       0x07
#define max7219_reg_digit7       0x08
#define max7219_reg_decodeMode   0x09
#define max7219_reg_intensity    0x0a
#define max7219_reg_scanLimit    0x0b
#define max7219_reg_shutdown     0x0c
#define max7219_reg_displayTest  0x0f

class LedMatrix 
{
    public:
        LedMatrix();
        void setup_dot_matrix();
        void display(int bpm);

    private:
        void write_to_max(int reg, int col);
        void pattern_to_display(char *pattern);
        void clear();

        SPI max_spi;
        DigitalOut spiLoad;

        char pattern_heart[8] = 
        {
            0b00000000,
            0b01100110,
            0b11111111,
            0b11111111,
            0b01111110,
            0b00111100,
            0b00011000,
            0b00000000
        };
};

#endif // PP_LED_MATRIX_HPP
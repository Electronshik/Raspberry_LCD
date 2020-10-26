#include <cstdio>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lcd.h"

#define Lcd_BACKLIGHT   0x08  // On
// Lcd_BACKLIGHT = 0x00  # Off

#define ENABLE  0b00000100 // Enable bit


_LCD::_LCD(unsigned char addr) :Addr{addr}, Cmd{0}, Data{1}
{
    if (wiringPiSetup() == -1) return;
    Fd = wiringPiI2CSetup(Addr);
    //printf("Fd = %d ", Fd);
    LcdSendByte(0x33, Cmd); // Initialise
    LcdSendByte(0x32, Cmd); // Initialise
    LcdSendByte(0x06, Cmd); // Cursor move direction
    LcdSendByte(0x0C, Cmd); // 0x0F On, Blink Off
    LcdSendByte(0x28, Cmd); // Data length, number of lines, font size
    LcdSendByte(0x01, Cmd); // Clear display
    delayMicroseconds(500);
}

// float to string
void _LCD::PrintFloat(float myFloat)
{
    char buffer[20];
    sprintf(buffer, "%4.2f", myFloat);
    PrintLn(buffer);
}

// int to string
void _LCD::PrintInt(int i)
{
    char array1[20];
    sprintf(array1, "%d", i);
    PrintLn(array1);
}

// clr Lcd go home loc 0x80
void _LCD::Clear(void)
{
    LcdSendByte(0x01, Cmd);
    LcdSendByte(0x02, Cmd);
}

// go to location on Lcd
void _LCD::GoTo(int line, int pos)
{
    if (line == 0)
    {
        LcdSendByte(0x80 + pos, Cmd);
    }
    else if (line == 1)
    {
        LcdSendByte(0xC0 + pos, Cmd);
    }
    //LcdSendByte(line, Cmd);
}

// out char to Lcd at current position
void _LCD::PrintChar(char val)
{
    LcdSendByte(val, Data);
}

// this allows use of any size string
void _LCD::PrintLn(const char* s)
{
    while (*s) LcdSendByte(*(s++), Data);
}

void _LCD::LcdSendByte(int bits, int mode)
{
    //Send byte to data pins
    // bits = the data
    // mode = 1 for data, 0 for command
    int bits_high;
    int bits_low;
    // uses the two half byte writes to Lcd
    bits_high = mode | (bits & 0xF0) | Lcd_BACKLIGHT;
    bits_low = mode | ((bits << 4) & 0xF0) | Lcd_BACKLIGHT;

    // High bits
    wiringPiI2CReadReg8(Fd, bits_high);
    lcd_toggle_enable(bits_high);

    // Low bits
    wiringPiI2CReadReg8(Fd, bits_low);
    lcd_toggle_enable(bits_low);
}

void _LCD::lcd_toggle_enable(int bits)
{
    // Toggle enable pin on Lcd display
    delayMicroseconds(500);
    wiringPiI2CReadReg8(Fd, (bits | ENABLE));
    delayMicroseconds(500);
    wiringPiI2CReadReg8(Fd, (bits & ~ENABLE));
    delayMicroseconds(500);
}

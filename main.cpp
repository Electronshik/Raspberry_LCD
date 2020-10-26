#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"

_LCD Lcd(0x3f);

//#define 0, 0  0x80 // 1st line
//#define 1, 0  0xC0 // 2nd line

int main()
{
    char array1[] = "Hello world!";

    while (1)
    {
        Lcd.GoTo(0, 0);
        Lcd.PrintLn("Using wiringPi");
        Lcd.GoTo(1, 0);
        Lcd.PrintLn("Geany editor.");

        delay(2000);
        Lcd.Clear();
        Lcd.GoTo(0, 0);
        Lcd.PrintLn("I2c  Programmed");
        Lcd.GoTo(1, 0);
        Lcd.PrintLn("in C not Python.");

        delay(2000);
        Lcd.Clear();
        Lcd.GoTo(0, 0);
        Lcd.PrintLn("Arduino like");
        Lcd.GoTo(1, 0);
        Lcd.PrintLn("fast and easy.");

        delay(2000);
        Lcd.Clear();
        Lcd.GoTo(0, 0);
        Lcd.PrintLn(array1);

        delay(2000);
        Lcd.Clear();
        Lcd.PrintLn("Int  ");
        int value = 20125;
        Lcd.PrintInt(value);

        delay(2000);
        Lcd.GoTo(1, 0);
        Lcd.PrintLn("Float ");
        float FloatVal = 10045.25989;
        Lcd.PrintFloat(FloatVal);
        delay(2000);
    }
    return 0;
}

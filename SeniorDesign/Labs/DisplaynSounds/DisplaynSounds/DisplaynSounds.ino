/*
  Lab 10: DisplaynSOunds

  Using a 16x2 3.3V LCD, we will program it to say various things.

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.

  We also need an external library added in, found here: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

  Download the respository and then place into the ardunio libraries folder as a zip.

  Go to sketch -> Include Libaries -> add .ZIP libary



*/

//LiquidCrystal is required to use the lcd
//Wire is required to communicate over I2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); \
int buz = 14;
int x = 0;
int y = 0;
int count = 0;
int freq = 200;


//Declare the pins that you are using, we are doing digial work so no analog pins needed
//GP pins 2-6 are being used.
void setup()
{
  lcd.begin();    //initialize lcd screen
  lcd.backlight();  // turn on the backlight
  lcd.setCursor(0, 0); //Set the cursor location to the first row, first column
  pinMode(buz, OUTPUT);
}

void rowF(void)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  x = 0;
  y = 0;
  while (y < 2)
  {
    while (x < 16)
    {
      lcd.setCursor(x, y);
      lcd.print("f");
      x++;
      delay(750);
      lcd.clear();
    }
    x = 0;
    y++;
  }
}

void bouncingF()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  x = 0;
  y = 0;
  while (x < 16)
  {
    while (y < 2)
    {
      lcd.setCursor(x, y);
      lcd.print("f");
      y++;
      delay(500);
      lcd.clear();
    }
    y = 0;
    x++;
  }
}

void bouncingFtoE()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  x = 0;
  y = 0;
  count = 0;

  while (x < 16)
  {
    while (y < 2)
    {
      lcd.setCursor(x, y);
      lcd.print("f");
      y++;
      delay(750);
      lcd.clear();
    }
    y = 0;
    x++;
  }
  while (x >= 0)
  {
    while (y >= 0)
    {
      lcd.setCursor(x, y);
      lcd.print("e");
      y--;
      delay(500);
      lcd.clear();
    }
    y = 1;
    x--;
  }
}

void loop()
{
  //tone(buz,220);
  //Clear the board in advance
  lcd.clear();
  lcd.setCursor(0, 0);
  x = 0;
  y = 0;
  count = 0;
  freq = 200;

  while (x < 16)
  {
    while (y < 2)
    {
      lcd.setCursor(x, y);
      lcd.print("f");
      y++;
      delay(750);
      lcd.clear();
    }
    y = 0;
    x++;
    tone(buz, freq);
    delay(250);
  }
  while (x >= 0)
  {
    while (y >= 0)
    {
      lcd.setCursor(x, y);
      lcd.print("e");
      y--;
      delay(500);
      tone(buz, freq);
      delay(250);
      lcd.clear();
    }
    y = 1;
    x--;
    freq += 25;
  }



}

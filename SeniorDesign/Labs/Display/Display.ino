/*
  Lab 4: Display

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


//Declare the pins that you are using, we are doing digial work so no analog pins needed
//GP pins 2-6 are being used.
void setup()
{
  //initialize lcd screen
  lcd.backlight();  // turn on the backlight
  lcd.setCursor(0, 0); //Set the cursor location to the first row, first column
}
void loop()
{
  //Clear the board in advance
  lcd.clear();
  lcd.setCursor(0, 0);
  //Print words to the first row
  lcd.print("Hello World!");
  //Look at the second row
  lcd.setCursor(0, 1);
  //Print words to the second row
  lcd.print("Lab 4 Display");
  delay(3000);
  //Look at the first row
  lcd.setCursor(0, 0);
  //Reprint to the first row
  lcd.print("Demonstration");
  delay(3000);
  //look at second row
  lcd.setCursor(0, 1);
  //Reprint to second row
  lcd.print("The Possibilites");
  delay(3000);
}

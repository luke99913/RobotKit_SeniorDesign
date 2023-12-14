/*
  Lab 6: Analog Inputs
  
  The raspberry pi pico has a 12 bit on-board acd, so it can measure voltage in 12 steps.

  In our set up, we must set the analogRead resoultion to 12, using the command in the setup function. 

  Since the ADC is 12 bit, its raw value will be anywhere from 0 - 4096

  Our calculated resoultion for this system is: (3.3/4096) = 0.8056
  
  When displaying the voltage, we will get an output of mV, so we should expect a value of somehwhere cloes to 3300 mV, plus or minus real world error.

  ADC Pins lie on GP pins 26 and 27

  For the analog inputs, every GPIO pin is capabile of PWM, so every GP pin can be analogRead()
  
  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ADCInput.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

int adc = 27;
int button1 = 9;

void setup()
{
  //Delcare pins as digital inputs and outputs
  lcd.begin();    //initialize lcd screen
  lcd.backlight();  // turn on the backlight
  lcd.setCursor(0, 0); //Set the cursor location to the first row, first column
  pinMode(adc, INPUT );
  pinMode(button1, INPUT);
  analogReadResolution(12);
}

void loop()
{
 lcd.setCursor(0, 0);
 lcd.print("Raw Value:");
 lcd.setCursor(11, 0);
 lcd.print( analogRead(adc) );
 delay(1000);
 lcd.setCursor(0, 1);
 lcd.print("mV:");
 lcd.setCursor(4, 1);
 lcd.print( analogRead(adc) * 0.8056);
 delay(1000);




}

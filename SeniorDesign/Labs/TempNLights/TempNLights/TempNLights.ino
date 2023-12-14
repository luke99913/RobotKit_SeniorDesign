/*
  Lab 11: TempnLights

  Using analog inputs from the tempature senseor, we will be able to do various things
  
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

int tempSence = 18;
float voltage = 0;                          //the voltage measured from the TMP36
float degreesC = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); 
void setup() {
  // put your setup code here, to run once:
  lcd.begin();    //initialize lcd screen
  lcd.backlight();  // turn on the backlight
  lcd.setCursor(0, 0); //Set the cursor location to the first row, first column
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  voltage = analogRead(18) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
  Serial.println(degreesC);
  delay(10000);
//  lcd.print(degreesC);
//  delay(3000);
//  lcd.setCursor(8,0);
//  voltage = analogRead(tempSence) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
//  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
//  lcd.print(degreesC);
//  delay(3000);
//  lcd.setCursor(13,0);
//  voltage = analogRead(tempSence) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
//  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
//  lcd.print(degreesC);
//  delay(3000);

}

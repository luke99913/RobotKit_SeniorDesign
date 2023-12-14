/*
  Lab 7: Servo 

  Using the tempature sensor, we are going to determine what the tempature is, and then turn the servo in relation to the tempature. 

  The tempature sensor with the flat facing towards the user: pin1: VCC pin2: Vout pin3:GND

  Servo: Brown: GRD RED: VCC ORANGE: PWM

  For the analog inputs, every GPIO pin is capabile of PWM, so every GP pin can be analogRead() or analogWrite()

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/

#include <Servo.h>
float temp;
Servo myservo; 
int servoPosition;
float voltage = 0;                          //the voltage measured from the TMP36
float degreesC = 0;
void setup()
{

  myservo.attach(3);
  Serial.begin(9600);
}

void loop()
{
  voltage = analogRead(2) * 0.004882813;   //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
  degreesC = (voltage - 0.5) * 100.0;       //convert the voltage to a temperature in degrees Celsius
  Serial.println(degreesC);
  servoPosition = map(degreesC, 0, 50, 180, 0);
  myservo.write(servoPosition);
  delay(1000);
//  servoPosition = 280;
//  myservo.write(servoPosition);
//  delay(1000);
}

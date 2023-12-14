/*
  Lab 1: Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  We are now able to use the Raspberry Pi Pico W microcontroller in conjunction with the Arduino IDE. 

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.

  
  
*/


//Define the pin we are going to use
int LED = LED_BUILTIN;
  
// the setup function runs once when you press reset or power the board
void setup() {
  //Set that pin to an input/output
  pinMode(LED, OUTPUT);
}

void loop() {
  //Turn the pin on 
  digitalWrite(LED , HIGH);
  //Wait 1000ms or 1sec
  delay( 1000 );
  //Tun the pin off
  digitalWrite(LED, LOW);
  //Wait 1000ms or 1sec
  delay(1000);
}

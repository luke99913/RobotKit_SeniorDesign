/*
  Lab 2: Touchless Sensor

  Using a Photoresisitor, a resistor that varies depending on the amoutn of light, we will turn on and off a LED without touching the circuit. 

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.

  
  
*/
//Declare the pins that you are using, we are doing digial work so no analog pins needed

int photo = 0;                      
int LED = 1;

void setup()
{
  //Delcare pins as digital inputs and outputs
  pinMode(photo, INPUT);
  pinMode(LED, OUTPUT);             
}

void loop()
{
  //Check to see if the photoresistor has enough light
  //digitalRead allow us to get a high or low value returned from a digital input 
  if (digitalRead(photo) == HIGH) 
  {
    digitalWrite(LED, HIGH);         // If HIGH, Turn on the LED
  } 
  else 
  {
    digitalWrite(LED, LOW);          // Else, if LOW, Turn off the LED
  }
}

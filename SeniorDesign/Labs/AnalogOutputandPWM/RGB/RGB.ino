/*
  Lab 5: Analog Outputs and PWM

  Using a RGB, we will experiment with changing(analog) outputs and input. 
  
  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/
//Declare the pins that you are using, we are doing digial work so no analog pins needed
//GP pins 2-6 are being used.
int red = 2;
int green = 3;
int blue = 4;
int loopyCounter;


void setup()
{
  //Delcare pins as digital inputs and outputs
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop()
{
  digitalWrite(red, HIGH);
  delay(1000);
  digitalWrite(red, LOW);
  delay(1000);
  digitalWrite(green, HIGH);
  delay(1000);
  digitalWrite(green, LOW);
  delay(1000);
  digitalWrite(blue, HIGH);
  delay(1000);
  digitalWrite(blue, LOW);
  delay(1000);
  loopyCounter = 0;
  while (loopyCounter < 256)
  {
    analogWrite(red, loopyCounter);
    analogWrite(green, loopyCounter);
    analogWrite(blue, loopyCounter);
    delay(10);
    loopyCounter = loopyCounter + 1;
  }
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);



}

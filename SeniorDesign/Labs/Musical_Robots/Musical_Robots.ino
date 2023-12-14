/*
  Lab 3: Musical Robotics

  Using a Photoresisitor, a resistor that varies depending on the amoutn of light, we will turn on and off a LED without touching the circuit. 

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.

  
  
*/
//Declare the pins that you are using, we are doing digial work so no analog pins needed
//GP pins 2-6 are being used. 
int buz = 2;
int button1 = 3;
int button2 = 4;
int button3 = 5;
int button4 = 6;


void setup()
{
  //Delcare pins as digital inputs and outputs
  pinMode(buz, OUTPUT);
  pinMode(button1, INPUT_PULLUP); 
  pinMode(button2, INPUT_PULLUP);             
  pinMode(button3, INPUT_PULLUP);             
  pinMode(button4, INPUT_PULLUP);             
 
}

void loop()
{
  if(digitalRead(button1)==LOW)
    tone(buz,220);
  if(digitalRead(button2)==LOW)
    tone(buz,247);
  if(digitalRead(button3)==LOW)
    tone(buz,261);
  if(digitalRead(button4)==LOW)
    tone(buz,294);
    
 
}

/*
  Lab 8: Motor Robot

  Using the integrated PWM pins of the Raspberry Pi Pico in conjunction with a motor controller, we will make an atonomus robot.

  We have to use the motor controller to drive the motors. See the circuit diagram for hook up guide.
  
  The bot should adavance forward for half a second, turn right, then back up a bit, making a weird circle motion.

  For the analog inputs, every GPIO pin is capabile of PWM, so every GP pin can be analogRead() or analogWrite()

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/
//Initalize to GP pins
int ai1 = 0;
int ai2 = 1;
int bi1 = 3;
int bi2 = 4;
int pwma = 2;
int pwmb = 5;
int but = 10;
int count = 0;

void setup()
{

  Serial.begin (9600);        //set up a serial connection with the computer TESTING PURPOSES


  //All outputs to drive mototrs
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
  pinMode(bi1, OUTPUT);
  pinMode(bi2, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(but, INPUT_PULLUP);
}

void forward( int power)
{
  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);

  analogWrite(pwmb, power);
  analogWrite(pwma, power);
}

void backwards( int power)
{
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, HIGH);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, HIGH);

  analogWrite(pwmb, power);
  analogWrite(pwma, power);
}

void left( int power, int gotime)
{
  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, HIGH);

  analogWrite(pwma, power);
  analogWrite(pwmb, power);
  delay(gotime);
}

void right( int power, int gotime)
{
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, HIGH);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);

  analogWrite(pwma, power);
  analogWrite(pwmb, power);
  delay(gotime);
}

void nogo(int wait)
{
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, LOW);

  analogWrite(pwma, 0);
  analogWrite(pwmb, 0);
  delay(wait);
}


void loop()
{
  if (digitalRead(but) == LOW && count == 0)
  {
    forward(100);
    delay(500);
    right(255,250);
    backwards(100);
    delay(250);
    count++;
  }
  else
  {
  analogWrite(pwma, 0);
  analogWrite(pwmb, 0);
  count =0;
  }
  

}

/*
  Lab 9: Drive Robot

  Using the code developed in lab 8, we will make the robot dive across distances

  I have split each action for this lab into functions, making coding easier. 

  For the analog inputs, every GPIO pin is capabile of PWM, so every GP pin can be analogRead() or analogWrite()

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/
//Initalize to GP pins
int ai1 = 0;
int ai2 = 1;
int bi1 = 3;
int bi2 = 6;
int pwma = 2;
int pwmb = 7;
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

void forward( int power, int gotime)
{
  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);

  analogWrite(pwmb, power + 10);
  analogWrite(pwma, power);
  delay(gotime);
}

void backwards( int power,int gotime)
{
  digitalWrite(ai1, LOW);
  digitalWrite(ai2, HIGH);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, HIGH);

  analogWrite(pwmb, power);
  analogWrite(pwma, power);
  delay(gotime);
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
void arch(int gotime)
{
  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);

  analogWrite(pwmb, 125);
  analogWrite(pwma, 100);
  delay(gotime);
  analogWrite(pwmb, 0);
  analogWrite(pwma, 0);
  
}


void loop()
{
//  forward(100, 10000);
//  right(100, 1100);
//  forward(100, 10000);
//  right(100, 1100);
//  forward(100, 10000);
//  left(100, 1100);
//  forward(100, 10000);
    
    if(digitalRead(but)==LOW && count == 0)
    {
      arch(5000);
      count++;
    }
    else if(digitalRead(but) == HIGH)
    {
      count = 0;
    }
    

}

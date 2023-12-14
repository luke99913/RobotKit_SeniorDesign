/*
  Lab 12: LineBot

  Using the photoSensor, we will read in its vaules. Using the analog values, we will determine the color of the tape we are to follow

  Driving the bot forward, we will continuously check the values under the robot for the tape. If we are not near the tape, we will turn towards the tape.
  
  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.

  We also need an external library added in, found here: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

  Download the respository and then place into the ardunio libraries folder as a zip.

  Go to sketch -> Include Libaries -> add .ZIP libary



*/
int ai1 = 0;
int ai2 = 1;
int bi1 = 3;
int bi2 = 6;
int pwma = 2;
int pwmb = 7;
int but = 10;
int light =0;
int lightSense = 20;
int minWhite = 0;
int count = 0;

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

void setup() {
  // put your setup code here, to run once:
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

void loop() {
  if(digitalRead(but)==LOW && count == 0)
    {
     if(analogRead(lightSense >= minWhite)
      {
        forward(100, 500);
        delay(500);
      }
      else if(analogRead(lightSense < minWhite)
      {
        left(100,500);
        delay(500);
      }
    }
    else if(digitalRead(but) == HIGH)
    {
      count = 0;
    }

}

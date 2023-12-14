/*
  Lab 12: LineBot

  Using the ultrasonic sensor, we will attempt to escape a structure.

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
const int trigPin = 20;           //connects to the trigger pin on the distance sensor
const int echoPin = 21;           //connects to the echo pin on the distance sensor
float distance = 0;               //stores the distance measured by the distance sensor
int count=0;


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

float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
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
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

}

void loop() {
  if(digitalRead(but)==LOW && count == 0)
    {
     if(getDistance() < 10)
      {
        right(100, 1000);
        delay(500);
      }
      else if(getDistance() > 10)
      {
        forward(100, 500);
        delay(500);
      }
      count++;
    }
    else if(digitalRead(but) == HIGH)
    {
      count = 0;
    }

}

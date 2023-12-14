/*
  Lab 7: UltraSonic Sensor

  Using the Ultra Sonic Sensor is easy to use

  We can use any GP pins we want for the echo and the trigger

  And it works off of 3.3V, for further distances, use 5V
  
  For the analog inputs, every GPIO pin is capabile of PWM, so every GP pin can be analogRead() or analogWrite()

  We are using the GP numbers on the pinout diagram found here: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html

  Unlike the pins on the board, the GP pin numbers start at 0, making the board index from 0-39.



*/

const int trigPin = 6;           //connects to the trigger pin on the distance sensor
const int echoPin = 7;           //connects to the echo pin on the distance sensor
float distance = 0;               //stores the distance measured by the distance sensor

void setup()
{

  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor
}

void loop() {
  distance = getDistance();   //variable to store the distance measured by the sensor

  Serial.print(distance);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  

  delay(50);      //delay 50ms between each reading
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

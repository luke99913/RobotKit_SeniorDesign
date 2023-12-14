#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#ifndef STASSID
#define STASSID "iPhone 13 mini (6)"
#define STAPSK "110816Iley"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

int ai1 = 0;
int ai2 = 1;
int bi1 = 3;
int bi2 = 6;
int pwma = 2;
int pwmb = 7;
int but = 10;

int lightSense = 27;

int port = 4242;

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiServer server(port);

struct SentData {
  int xValue;
  int yValue;
  int potValue;
};

int motorCool = 15;


void setup() {
  pinMode(ai1, OUTPUT);
  pinMode(ai2, OUTPUT);
  pinMode(bi1, OUTPUT);
  pinMode(bi2, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(but, OUTPUT);

  analogReadResolution(10);
  

  lcd.init();
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("PicoW2");

  Serial.printf("Connecting to '%s' with '%s'\n", ssid, password);

  lcd.setCursor(0, 0);
  lcd.print("Connecting to:");
  lcd.setCursor(0, 1);
  lcd.printf("'%s'", ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.setCursor(0, 0);
    lcd.print("Connecting to:");
    lcd.setCursor(0, 1);
    lcd.printf("'%s'...", ssid);
    delay(100);
  }

  Serial.printf("\nConnected to WiFi\n\nConnect to server at %s:%d\n", WiFi.localIP().toString().c_str(), port);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connected to wifi:");
  lcd.setCursor(0, 1);
  lcd.printf("'%s'", ssid);
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);              // column = 0, row = 0, 20 columns 0 to 19, 2 rows 0 to 1
  lcd.print("Connect to:");              // write text to LCD
  lcd.setCursor(0, 1);              // position cursor column = 5, row = 1
  lcd.printf("%s:%d", WiFi.localIP().toString().c_str(), port);

  server.begin();
}

void loop() {

  digitalWrite(ai1, LOW);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, LOW);

  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    bool forw, back, spin;
    int del = 125;

    while (true) {
      Serial.print("lightSense: ");
      Serial.println(analogRead(lightSense));

      /*if (analogRead(lightSense) > 3950) 
      {
        while (true) {
          spins(0, 0);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("You Loose!");
          delay(10000);
        }
      }*/

      // Read the entire structure sent by the client
      SentData currentData;
      client.read(reinterpret_cast<uint8_t*>(&currentData), sizeof(currentData));

      // Do something with the received data
      Serial.print("X-Value: ");
      Serial.println(currentData.xValue);
      Serial.print("Y-Value: ");
      Serial.println(currentData.yValue);



      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("X-Value: ");
      lcd.print(currentData.xValue);
      lcd.setCursor(0, 1);
      lcd.print("Y-Value: ");
      lcd.print(currentData.yValue);

      if (currentData.yValue > 0) {
        if (back) {
          backwards(motorCool, motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else if (spin) {
          spins(motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else {
          forwards(currentData.xValue, abs(currentData.yValue), currentData.potValue);
          delay(del);
        }
        forw = true;
        back = false;
        spin = false;
      }

      else if (currentData.yValue < 0) {
        if (forw) {
          forwards(motorCool, motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else if (spin) {
          spins(motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else {
          backwards(currentData.xValue, abs(currentData.yValue), currentData.potValue);

          delay(del);
        }
        forw = false;
        back = true;
        spin = false;
      }

      else {
        if (forw) {
          forwards(motorCool, motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else if (back) {
          backwards(motorCool, motorCool, currentData.potValue);
          digitalWrite(ai1, LOW);
          digitalWrite(ai2, LOW);
          digitalWrite(bi1, LOW);
          digitalWrite(bi2, LOW);
          delay(del);
        }
        else {
          spins(currentData.xValue, currentData.potValue);
          delay(del);
        }
        forw = false;
        back = false;
        spin = true;
      }
    }
  }
}


void forwards(int xValue, int yValue, int potValue)
{
  int left;
  int right;

  Serial.println(xValue);
  Serial.println(yValue);

  //turn right
  if (xValue > 0) {
    left = yValue;
    right = int(float(yValue) * (256.0 - float(abs(xValue))) / 256.0);
  }

  //turn left
  else if (xValue < 0) {
    left = int(float(yValue) * (256.0 - float(abs(xValue))) / 256.0);
    right = yValue;
  }

  // go straight
  else {
    left = yValue;
    right = yValue;
  }

  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);
  analogWrite(pwmb, left);
  analogWrite(pwma, right);
}


void backwards(int xValue, int yValue, int potValue)
{
  int left;
  int right;

  Serial.println(xValue);
  Serial.println(yValue);

  //turn right
  if (xValue > 0) {
    left = int(float(yValue) * (256.0 - float(abs(xValue))) / 256.0);
    right = yValue;
    
  }

  //turn left
  else if (xValue < 0) {
    left = yValue;
    right = int(float(yValue) * (256.0 - float(abs(xValue))) / 256.0);
  }

  // go straight
  else {
    left = yValue;
    right = yValue;
  }
  Serial.print("Left: ");
  Serial.println(left);
  Serial.print("Right: ");
  Serial.println(right);

  digitalWrite(ai1, LOW);
  digitalWrite(ai2, HIGH);
  digitalWrite(bi1, LOW);
  digitalWrite(bi2, HIGH);
  analogWrite(pwmb, left);
  analogWrite(pwma, right);
}

void spins(int xValue, int potValue)
{
  int spinSpeed;

  Serial.println(xValue);

  //turn right
  if (xValue > 0) {
    digitalWrite(ai1, LOW);
    digitalWrite(ai2, HIGH);
    digitalWrite(bi1, HIGH);
    digitalWrite(bi2, LOW);
    spinSpeed = abs(xValue);
  }

  //turn left
  else if (xValue < 0) {
    digitalWrite(ai1, HIGH);
    digitalWrite(ai2, LOW);
    digitalWrite(bi1, LOW);
    digitalWrite(bi2, HIGH);
    spinSpeed = abs(xValue);

  }

  // stop
  else {
    digitalWrite(ai1, LOW);
    digitalWrite(ai2, LOW);
    digitalWrite(bi1, LOW);
    digitalWrite(bi2, LOW);
  }

  analogWrite(pwmb, spinSpeed);
  analogWrite(pwma, spinSpeed);
}

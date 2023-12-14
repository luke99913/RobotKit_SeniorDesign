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

int port = 4242;

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiServer server(port);

struct SentData
{
  float xValue;
  float yValue;
};

void forward(int powerb, int powera)
{
  digitalWrite(ai1, HIGH);
  digitalWrite(ai2, LOW);
  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, LOW);

  Serial.println(powerb);
  Serial.println(powera);
  analogWrite(pwmb, powerb);
  analogWrite(pwma, powera);
  delay(250);
}
void setup()
{
  lcd.begin();    //initialize lcd screen
  lcd.begin();    //initialize lcd screen

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
  while (WiFi.status() != WL_CONNECTED)
  {
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

  lcd.clear();
  lcd.setCursor(0, 0);              // column = 0, row = 0, 20 columns 0 to 19, 2 rows 0 to 1
  lcd.print("Connect to:");              // write text to LCD
  lcd.setCursor(0, 1);              // position cursor column = 5, row = 1
  lcd.printf("%s:%d", WiFi.localIP().toString().c_str(), port);

  server.begin();
}

void loop()
{
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("client Conntected");
    // Read the entire structure sent by the client
    SentData currentData;
    client.read(reinterpret_cast<uint8_t*>(&currentData), sizeof(currentData));
    if ((currentData.xValue > 0) || (currentData.yValue > 0))
    {
      forward(int(abs(currentData.xValue)), int(abs(currentData.yValue)));

      //Serial.println(int(abs(currentData.xValue)));
      //Serial.println(int(abs(currentData.yValue)));

      lcd.setCursor(0, 0);
      lcd.print("X-Value: ");
      lcd.print(currentData.xValue);
      lcd.setCursor(0, 1);
      lcd.print("Y-Value: ");
      lcd.print(currentData.yValue);

    }

    // Do something with the received data
    Serial.print("Received Line One: ");
    Serial.println(currentData.xValue);
    Serial.print("Received Line Two: ");
    Serial.println(currentData.yValue);

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("X-Value: ");
    lcd.print(currentData.xValue);
    lcd.setCursor(0, 1);
    lcd.print("Y-Value: ");
    lcd.print(currentData.yValue);


    delay(50);
  }





}

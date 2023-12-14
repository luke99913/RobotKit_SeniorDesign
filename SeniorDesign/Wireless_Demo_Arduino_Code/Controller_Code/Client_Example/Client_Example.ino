#include <WiFi.h>
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#ifndef STASSID
#define STASSID "iPhone 13 mini (6)"
#define STAPSK "110816Iley"
#endif

#define I2C_SDA 12
#define I2C_SCL 13

const char* ssid = STASSID;
const char* password = STAPSK;

const char* host = "172.20.10.5";
const uint16_t port = 4242;

const int potPin = 28;

struct SentData {
  int xValue;
  int yValue;
  int potValue;
};

float timer, timeOut;

// Define dead zone and max
float deadZone = 15.0;
float maxAngle = 30.0;
float joyDeadZone = 12.0;

Adafruit_MPU6050 mpu;

WiFiMulti multi;

void setup() {
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on

  Wire.setSDA(I2C_SDA);
  Wire.setSCL(I2C_SCL);

  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  // Start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  multi.addAP(ssid, password);

  if (multi.run() != WL_CONNECTED) {
    Serial.println("Unable to connect to network, rebooting in 1 seconds...");
    delay(1000);
    rp2040.reboot();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(0, HIGH);
  WiFiClient client;

  SentData currentData;

  // Connect to the server
  if (client.connect(host, port)) {
    Serial.println("Connected to server");



    while (true) {

      currentData.potValue = analogRead(potPin) / 4;
      if (currentData.potValue > 210)
     {
        currentData.potValue = 210;
     }
      if (currentData.potValue < 95)
      {
        currentData.potValue = 95;
      }
      bool joy = isJoyActivated();

      if (!joy) {
        
        float roll, pitch, yaw;
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        // Calculate pitch and roll
        pitch = atan2(a.acceleration.x, sqrt(pow(a.acceleration.y, 2) + pow(a.acceleration.z, 2))) * 180.0 / PI;
        roll = atan2(a.acceleration.y, sqrt(pow(a.acceleration.x, 2) + pow(a.acceleration.z, 2))) * 180.0 / PI;

        if (abs(pitch) > maxAngle | abs(roll) > maxAngle) {
          // start timer
          if (timer > timeOut) {
            // Send stopped values to robot
          }
        }
        else {
          // stop timer
        }

        // Normalize accelerometer values
        float rSign = 1.0;
        float pSign = 1.0;
        if (pitch < 0.0) {
          pSign = -1.0;
        }
        if (roll < 0.0) {
          rSign = -1.0;
        }

        Serial.print("Pitch: ");
        Serial.println(pitch);
        Serial.print("Roll: ");
        Serial.println(pitch);

        float normPitch = 0.0;
        float normRoll = 0.0;
        if (abs(pitch) > maxAngle) {
          normPitch = 1.0 * pSign;
        }
        if (abs(roll) > maxAngle) {
          normRoll = 1.0 * rSign;
        }
        if (abs(pitch) < deadZone) {
          normPitch = 0.0;
        }
        if (abs(roll) < deadZone) {
          normRoll = 0.0;
        }
        if (abs(pitch) < maxAngle && abs(pitch) > deadZone) {
          normPitch = normalize((abs(pitch) - deadZone) * pSign, -1.0 * (maxAngle - deadZone), 1.0 * (maxAngle - deadZone));
        }
        if (abs(roll) < maxAngle && abs(roll) > deadZone) {
          normRoll = normalize((abs(roll) - deadZone) * rSign, -1.0 * (maxAngle - deadZone), 1.0 * (maxAngle - deadZone));
        }

        Serial.print("normPitch: ");
        Serial.println(normPitch);
        Serial.print("normRoll: ");
        Serial.println(normRoll);

        // Multiply by potentiometer value
        currentData.xValue = (normRoll * -1.0) * currentData.potValue;
        currentData.yValue = normPitch * currentData.potValue;
      }

      if (joy) {

        float joyX = analogRead(27) - 512.0;
        float joyY = analogRead(26) - 512.0;

        // Normalize joystick values
        float xSign = 1.0; 
        float ySign = 1.0;
        if (joyX < 0.0) {
          xSign = -1.0;
        }
        if (joyY < 0.0) {
          ySign = -1.0;
        }
        
        float normJoyX = 0.0;
        float normJoyY = 0.0;
        if (abs(joyX) < joyDeadZone) {
          normJoyX = 0.0;
        }
        if (abs(joyY) < joyDeadZone) {
          normJoyY = 0.0;
        }
        if (abs(joyX) > joyDeadZone) {
          normJoyX = normalize((abs(joyX) - joyDeadZone) * xSign, -512.0 + joyDeadZone, 512.0 - joyDeadZone);
        }
        if (abs(joyY) > joyDeadZone) {
          normJoyY = normalize((abs(joyY) - joyDeadZone) * ySign, -512.0 + joyDeadZone, 512.0 - joyDeadZone);
        }
        
        // Multiply by potentiometer value
        currentData.xValue = int((normJoyX * -1.0)  * currentData.potValue);
        currentData.yValue = int(normJoyY * currentData.potValue);
      }

      Serial.print("X-Value: ");
      Serial.println(currentData.xValue);
      Serial.print("Y-Value: ");
      Serial.println(currentData.yValue);
      
      // Send the entire structure to the server
      client.write(reinterpret_cast<const uint8_t*>(&currentData), sizeof(currentData));
      delay(450);
    }
  }
  else {
    Serial.println("Connection to server failed");
    delay(5000);
  }

}


float normalize(float value, float minVal, float maxVal)
{
  return 2.0 * (value - minVal) / (maxVal - minVal) - 1.0;
}


bool isJoyActivated() {
  Serial.println(digitalRead(15));
  return !digitalRead(15) == HIGH;  // Assuming HIGH when the switch is ON
}

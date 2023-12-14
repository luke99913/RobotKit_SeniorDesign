# RobotKit_SeniorDesign
 Senior Design Robot Kit and Controller for Introduction to Robotics Classes

The primary objective of this project was to redesign and manufacture a new robotics kit for use in the Introduction to Robotics class. The new kit is intended to fix the shortcomings of the old kit when it came to ease of use and reliability. Within the new kit the customer requested that a Raspberry Pi Pico be used, new DC motors with motor encoders are chosen, and the microcontroller should be Arduino IDE compatible. 

The secondary objective of this project was to design the robot with the intention of making a “Sumo Bot” demonstration for STEM outreach events. The plan was to have the robot kit have an onboard wireless connection that would talk with a developed controller. The controller would either be tilt or joystick activated and would drive the robot according to the direction inputted by the user. The body of the robot would also be capable of protecting the microcontroller as another robot crashed into it, attempting to push it out of the ring.  

 Software 

Software Design for Robot Vehicle (Acting as Wi-Fi Server) 

Introduction: This section outlines the design and functionality of the PicoW2 robot control program, which serves as a Wi-Fi server for remote control. The program is developed using the Arduino framework and facilitates robot movement based on input from a client. It covers the design aspects, dependencies, configurations, and initialization procedures of the robot control program. 

Dependencies: The program relies on the following libraries: 

WiFi.h: For handling Wi-Fi connectivity. 

LiquidCrystal_I2C.h: For interfacing with the LCD screen. 

Wire.h: For I2C communication. 

Configuration 

ai1, ai2, bi1, bi2: Pins for motor control. 

pwma, pwmb: PWM control pins for motor speed. 

lightSense: Pin for a light sensor. 

STASSID, STAPSK: Wifi network SSID(or IP) and password 

port: Port number for the server. 

Server Initialization 

Initializes a WiFi server on the specified port. 

Creates a structure (SentData) to hold data received from the client. 

Sets a default cooling motor voltage (motorCool). 

Setup Function 

Configures motor control pins, sets analog read resolution, and initializes the LCD. 

Configures WiFi settings and establishes a connection. 

Displays connection details on the serial monitor and LCD. 

Starts the server and displays server IP on the LCD for client use. 

Main Loop 

Resets motor control pins to LOW voltage. 

Checks for incoming client connections. 

If a client is connected, enters an infinite loop to receive and process data. 

Data Reception and Processing 

Reads data sent by the client into the currentData structure. 

Displays received data on the serial monitor and LCD. 

Controls motor movement based on received data. 

Movement Control Functions  

Forwards: 

Controls forward movement upon receiving a positive Y value. 

The Y value also controls the overall speed of the motors. 

Adjusts motor speed to change direction based on the X value.
 
 

Backwards: 

Controls backward movement upon receiving a negative Y value. 

The Y value also controls the overall speed of the motors. 

Adjusts motor speed to change direction based on the X value. 


 
 

Spin: 

Controls spinning movement upon receiving a zero Y value. 

Adjusts motor speed and direction based on the sign and value of X. 

Conclusion The program successfully establishes a WiFi server, receives input from a client, and controls the robot's movement based on the received data. The movement is determined by the X and Y values, with different functions for forward, backward, and spinning motions. The LCD screen provides status updates, and the serial monitor logs relevant information. 

Note The specific functionalities related to the light sensor and an unspecified button are mentioned in the code but commented out. These functionalities can be troubleshooted and integrated into the sumo bot program. 

Software Design for Remote Control (Acts as WiFi Client) 

Introduction: This section provides a detailed overview of the software design for the Arduino program responsible for remote controlling the robot. The program reads sensor data from an MPU6050 sensor, potentiometer, and joystick, establishing a WiFi connection to send the data to the server (Robot Kit). It covers key components, data structures, code structure, and dependencies for the remote-control program. 

Dependencies: 

WiFi.h: For handling WiFi connectivity. 

Adafruit_MPU6050.h: For handling the Accelrometer/gyro 

Adafruit_Sensor.h: For handling sensor readings 

Wire.h: For I2C communication. 

Key Components  

MPU6050 Sensor - Reads accelerometer data with custom I2C pins. 2.2.2 

Joystick - Reads analog data from two joystick pins. - Used to control sensor data if activated.  

WiFi Connection - Uses Pico W WiFi module for connecting to a WiFi network.  

Potentiometer - Reads analog data from a potentiometer. - Controls the magnitude of sensor data. 

Configuration 

I2C_SDA, I2C_SCL: For MPU-6050 communication 

STASSID, STAPSK: Wifi network SSID(or IP) and password  

host, port: server identified by IP address and port. - Sends sensor data to the server. 

potPin: For potentiometer communication 

Communicated Data Structure 

A structure named SentData stores sensor data, including X and Y values and the potentiometer value to send to the Robot over the wifi network. 

Setup Function: 

Pin Initialization - Configures default LED pin and custom I2C pins. 

Serial Communication - Initializes serial communication for debugging. 

MPU6050 Initialization - Initializes the MPU6050 sensor with specific ranges and bandwidth.  

WiFi Connection - Connects to the WiFi network using provided credentials. - Reboots if connection fails. 

Main Loop: 

Client Initialization - Initializes a new WiFi client for server communication.  

SentData Initialization - Initializes the currentData struct used for data communication. 

Sensor Data Collection - Reads potentiometer value and checks for joystick activation. - Reads accelerometer data if joystick is not activated. Reads joystick values if joystick is activated.  

Data Normalization - Normalizes pitch and roll values considering dead zones and maximum angles or normalizes joystick values considering just dead zones. - Multiplies normalized values by the potentiometer value and loads the values into the currentData struct.  

Data Transmission - Sends the entire SentData structure named currentData to the server. 

Conclusion This section provides an in-depth understanding of the software design for the Arduino program. It covers key components, data structures, code structure, and dependencies. Developers can use this document as a reference for maintenance and future enhancements. 

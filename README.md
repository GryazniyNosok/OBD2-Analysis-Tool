# OBD2-Analysis-Tool

## What's this?
A simple system that uses Arduino Mega to read information from the car's computer using OBD2. Here it also displays that information on 0.96 inch OLED screens.

## What I used
  - Arduino Mega
  - SparkFun OBD Shield
  - 6 OLED screens
  - TCA9548A Multiplexer
  - ESP32

## How it works?
Arduino mega sends OBD2 codes (https://en.wikipedia.org/wiki/OBD-II_PIDs) to the SparkFun shield, which then sends requests to the OBD2 and expect the readable data back. Then the information received gets decoded and displayed on the OLED screens. 

ESP32 is used to create a bluetooth connection so I can connect to the system with my phone and read data from it.

## Pictures!


![Photo3_SolderingNightmare2](https://github.com/user-attachments/assets/c28ccbc4-6efb-4b7c-ad46-54433d03946d)
![Final Look](https://github.com/user-attachments/assets/cd5a17ae-caa3-4034-8165-2d737e84ebab)


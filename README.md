# OBD2-Analysis-Tool
A car diagnotics system that uses OBD2 port to read data from a car.
Components used:
  - Arduino Mega
  - SparkFun OBD Shield
  - 6 OLED screens
  - TCA9548A Multiplexer
  - ESP32
![Photo3_SolderingNightmare2](https://github.com/user-attachments/assets/c28ccbc4-6efb-4b7c-ad46-54433d03946d)
![Final Look](https://github.com/user-attachments/assets/cd5a17ae-caa3-4034-8165-2d737e84ebab)

# Car_Project_Prototype_Optimised
The main code for Arduino Mega. It requests data by sending specific codes ("010C" for RPM) to the OBD2 port via Sparkfun OBD shield and then receives the value back. This data then gets displayed on dedicated OLED screens through a multiplexer (Mega can't support more than 2 OLED screens by itself) and sent to the serial port for the ESP32 to read. 

# Car_Project_ESP32 
An ESP32 that reads data from the Arduino Mega serial port and then transmits it via BLE to a connected mobile device. 

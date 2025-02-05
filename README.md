# OBD2-Analysis-Tool
A car diagnotics system that used OBD2 port to read data from a car.

# Car_Project_Prototype_Optimised
The main code for Arduino Mega. It requests data by sending specific codes (010C for RPM) to the OBD2 port via Sparkfun OBD shield and then receives the value back. This data then gets displayed on a dedicated OLED screen and sent to the serial port for the ESP32. TODO

# Car_Project_ESP32 
An ESP32 that read data from the Arduino Mega serial port and then transmits it via BLE to any connected device. TODO

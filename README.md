# Design and implementation of the IoT in-home display
## Features 
- 15-minute kWh load profile on an LCD display
- A user-friendly GUI on mobile application for kWh consumption logging 
- Predict monthly energy consumption through algorithm
- Estimated bill prediction during the month
- High bill alert notification on mobile application
- Online energy consumption and bill monitoring through internet
## Conceptual Design 
![conceptual_design](https://user-images.githubusercontent.com/30025620/158118174-94ccc38f-40c2-4ccc-a24d-6c9c8ddffe8f.png)
## System Components
- ESP8266 Controller with Ax Wi-Fi
- ADS1115 Analog to Digital Converter
- ZMPT101B Voltage Sensor
- ACS712 Current Sensor
## Task Distribution
- [HW A1.1]  ADS1115 (ADC) Communication with ESP8266
- [HW B1.1]  ZMPT101B (Voltage Sensor) Communication with ESP8266
- [HW C1.1]  ACS712 (Current Sensor) Communication with ESP8266
- [HW A1.2]  Read both voltage and current sensor through ADC in ESP8266
- [HW D1.1]  LCD display/operate with ESP8266
- [SW A1.1]  Load prediction and Energy Consumption Algorithm
- [SW B1.1]  Implementation(code) of load prediction and energy consumption on Hardware
- [SW C1.1]  NetPie platform GUI for dashboard and mobile application
## Software Flowchart
![image](https://user-images.githubusercontent.com/30025620/158118542-af3b5956-dbc1-419e-a746-72fb8b43d2b8.png)
## Timeline of Project 
![timeline](https://user-images.githubusercontent.com/30025620/158118685-111221d4-c112-4ca1-9225-d90da078178c.png)

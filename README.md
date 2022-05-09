# Design and implementation of the IoT in-home display
- Note: The workshops uploaded in the main branch are done by all three group members (Muhammad Ashhab Khan, Sana Khurram, Muhammad Hamza Zafar)
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
# Weekly progress and issues faced
## Week 1
### Tasks
- Design finalisation 
- Workshops completed
### Problems
- N/A 
## Week 2
### Tasks 
- Components ordered
### Problems
- Time was consumed in procurement of hardware components(i.e ADS1115, ZMPT101B and ACS7120) which were received in the next week.
## Week 3
### Tasks 
- ADS1115 communication with ESP8266
- ZMPT101B communication with ESP8266
### Problems
- Unable to read voltage from ADS1115 as soldering was required along with a multimeter to test actual values of voltage. 
- Readings couldnt be verified at home as multimeter was required
## Week 4 
### Tasks 
- DC and AC power supplies were required for operating current and voltage sensor 
### Problems
- We tried calibrating the sensor with direct 220V AC at home but a multimeter was required in order to verify the readings. 
## Week 5 
### Tasks 
- Read both voltage and current sensor through ADc in ESP8266
- LCD display/operate with ESP8266
- Verified working of current sensor, ADS1115 and voltage sensor in TGGS lab as DC and AC power supplies were required from the lab  
- Load prediction and energy consumption algorithm (in progress)

## Week 6
### Problems
- Due to the issue of using different caliberation parameters for external ADC, we shifted to read voltage and current via MUX
### Task
- So as a new task we connected current and voltage sensors to 2 channels of multiplexer which is further connexted to the omly analog pin of NodeMCU
## Week 7
 - The energy consumption algorithm and the load prediction algorithms are implemented on the microcontroller.
## Week 8
 - GUI is made on the NETPIE platform and the parameters from the code are then send to the NETPIE
![1](https://user-images.githubusercontent.com/41298576/161098615-6d3255c9-f6e6-426b-aa62-10c5ddfcd59c.jpeg)
![2](https://user-images.githubusercontent.com/41298576/161098638-45c66744-c548-468f-a5fb-298194845449.jpeg)


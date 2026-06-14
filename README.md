<p align="center">
 <img width="700" height="200" alt="Crowd_Guard" src="https://github.com/user-attachments/assets/acad20d2-2193-4b4c-aaeb-b5ae00c71323" />
</p>

Smart Crowd Density System detects individuals in public areas. using the number of people entering, to regulate crowds with its features. Specifically in malls and metros that are full of people.

## ⚽ Purposes
- In Egypt, eleven grand challenges cause multiple issues, one of which is to reduce urban congestion, where Egypt is one of the most crowded regions in the world.
- Specifically in Cairo, it has a problem that comes from the reduced urban congestion grand challenge, which is the overcrowding in closed places such as malls and metros.
- Cairo ranks as the 7th most crowded city in the world.
- I face many decreases in public services, or accidents happen, even leading to death, in closed places, due to overcrowding.

## 📄 Description
- Crowd Guard is like a keeper of your place, which won't let the overcrowding flow into the location. 
- It balanced the number of people inside the place by detecting their number with the ultrasonic sensor, which connects to the microcontroller Atmega328p. Moreover, displaying the number on the LCD screen.
- There are two ultrasonic sensors, one in the entrance and the other in the exit. When anyone enters the place, they will be detected by the ultrasonic entrance and counted on the LCD. On the other hand, when anyone leaves the place, the exit ultrasonic sensor will decrease the number on the LCD
- When it determines the number of people over the limit that the place can handle, it shows a warning on the LCD screen and turns on the red light with a buzzer sound to warn people. 
- When the limit returns to the regular number of individuals, the red light will turn off and a green light will turn on, removing the LCD warning. 


## 📈 Usage
1. The system will be applied in real life, particularly in metros and malls, because they are the most crowded places.
 - The system will be connected with smart doors, where the limit exists, the doors will be closed.
 - For example, in the motor station, when the number exceeds the limit, the entrance will be closed until the number returns to normal. Furthermore, the screen will show another unsaturated station to direct people who couldn’t enter. 
2. When the system is set up in this way, it will 
 - Manage the crowd
 - Address the consequences of being crowded in closed places, including a decrease in public services, or save people from disasters.

 ## 🛠️ Bill of Materials (BOM)
 | Component | Quantity | Price | Purchase link |
 | :--- | :---: | :--- | :--- |
 | **ATMEGA328P-U** | 1 | 3.63$ | https://free-electronic.com/product/atmega328p-u/ |
 | **Ultrasonic sensor** | 2 | 1.51$ | https://free-electronic.com/product/ultrasonic-sensor-hc-sr04/ |
 | **Breadboard** | 2 | 0.94$ | https://free-electronic.com/product/breadboard-soldless-400-tie-points/ |
 | **LCD 16x2** | 1 | 1.24$ | https://free-electronic.com/product/lcd1602-blue-backlight-with-soldering-pin-header/ |
 | **LED60 mixed colors** | 1 | 0.85$ | https://free-electronic.com/product/led60-mixed-color-led-size-5mm-in-box/ |
 | **65pcs jumper wires** | 1 | 0.75$ | https://free-electronic.com/product/65pcs-flexible-breadboard-jumper-wires/ |
 | **passive buzzer** | 1 | 0.47$ | https://free-electronic.com/product/passive-buzzer-module/ |  
 | **resistor** | 10 | 0.14$ | https://free-electronic.com/product/resistor-15-ohm-1w/ | 
 | **Battery** | 1 | 2.39$ | https://free-electronic.com/product/9v-varta-longlife-power-alkaline-battery/ | 
 | **Battery Holder ( 9V )** | 1 | 0.23$ | https://free-electronic.com/product/battery-holder-9v/ |
 | **Voltage Regulator** | 1 | 3.34$ | https://free-electronic.com/product/dc-voltage-regulator-buck-converter-6-36v-to-1-25-32v-5a-constant-current-voltage-mppt-solar-controller/ |
 | **Crystal (16 MHz)** | 1 | 0.076$ | https://free-electronic.com/product/crystal-2-pin-16-mhz/ |
 | **Capacitor (22pF)** | 1 | 0.019$ | https://free-electronic.com/product/ceramic-capacitor-22pf-50v/ |
 | **Capacitor (100pF)** | 1 | 0.019$ | https://free-electronic.com/product/ceramic-capacitor-100nf-50v/ |
 | **Resistor (220 ohm)** | 10 | 0.29$ | https://free-electronic.com/product/resistor-220-ohm-3w/ |
 | **Pin Header 1x4** | 2 | 0.058$ | https://www.ram-e-shop.com/shop/ph35-1x4-female-ph35-pin-header-female-1x4-straight-2-54mm-6976?category=52 |
 | **Total Price** | | 15.952$ | |
 
## 🔌 Wiring Diagram & Pinouts
* **Ultrasonic sensor 1 (IN):** Trig -> Pin 5, Echo -> Pin 4
* **Ultrasonic sensor 2 (OUT):** Trig -> Pin 3, Echo -> Pin 2
* **LCD Display (16x2):** Rs -> Pin 7, E -> Pin 8, DB4 -> Pin 9, DB5 -> Pin 10, DB 6 -> Pin 11, DB7 -> Pin 12
* **Indicators:** Red LED -> A0, Green LED -> A1, Buzzer -> Pin 6

## 🤖 Arduino code 

```cpp
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // shows the pins of the LCD that connect to Arduino 
int trigPin1 = 5;
int echoPin1 = 4;
int trigPin2 = 3;
int echoPin2 = 2;
int maxpeople = 5;  // maxiumim number of people can enter the place and it is 5
int redLed = A0;
int greenLed = A1; 
int buzzer = 6;
int count = 0;  // start count the number of people from 0   
long duration;  // the time it takes for the ultrasonic to send the waves and return back
long distance;  // its the distance comes from the duration and using the equition of the speed
bool sensor1Triggered = false;  // if the sensor number 1 detect move
bool sensor2Triggered = false;  // if the sensor number 1 detect move

void setup() {
  pinMode(trigPin1, OUTPUT);  // make the trig side from the first ultra sonic send waves
  pinMode(echoPin1, INPUT);  // make the echo side from the first ultra sonic reseive the wave that comes from trig side if it reflect 
  pinMode(trigPin2, OUTPUT);  // make the trig side from the second ultra sonic send waves 
  pinMode(echoPin2, INPUT);  // make the echo side from the second ultra sonic reseive the wave that comes from trig side if it reflect
  pinMode(redLed, OUTPUT);  // the red LED display light 
  pinMode(greenLed, OUTPUT);  // the green LED display light 
  pinMode(buzzer, OUTPUT);  // buzzer turn on and makes sound 
  lcd.begin(16, 2);  // turn on the LCD and determine its size
  lcd.setCursor(0, 0);  // stop the mouse in the first line 
  lcd.print("visitors: 0");  //start show the first stetment which is people = 0
  digitalWrite(greenLed, HIGH);  // in the first the green light only turn on and the red light and the buzzer is off
  digitalWrite(redLed, LOW);
  digitalWrite(buzzer, LOW);
}
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);  // the trig side start with stop working 
  delayMicroseconds(2);  // the trig starts working after 2e-6 seconds 
  digitalWrite(trigPin, HIGH);  // trig starts working 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);  // calculate the time for the wave to return back
  if (duration == 0) {
    return 100;  // if the wave does not reflected consider a 100cm for seafty 
  }
  distance = (duration * 0.0343) / 2;  // formula to determine the distance 
  return distance;
}
void loop() {
  int d1 = getDistance(trigPin1, echoPin1);  //calculate the first sensor read and save it 
  int d2 = getDistance(trigPin2, echoPin2);  //calculate the second sensor read and save it 
  
    if (d1 > 5 && d1 < 20 && !sensor1Triggered) {   // if the first sensor detect one in between 5 to 20cm 
    sensor1Triggered = true;  // so make it do the order 
  }
  
  if (sensor1Triggered && d2 > 5 && d2 < 20) {  // if the second sensor detect one in between 5 to 20cm
    if (count < 99) {  // thus increase the number of poeple 1 but cant be more than 99
      count++;
    }
    sensor1Triggered = false;  // return the first sensor to the standerd state until the anothe one move and be detected 
    sensor2Triggered = false;  // return the  second sensor to the standerd state until the anothe one move and be detected 
    delay(300);  // every 0.3 seconds send another signal 
  }
  
    if (d2 > 5 && d2 < 20 && !sensor2Triggered) {
    sensor2Triggered = true;
  }
  
  if (sensor2Triggered && d1 > 5 && d1 < 20) {
    if (count > 0) {
      count--;  // if one move from sensor two then sensor one this means someone get out the place thus decreasing one 
    }
    sensor1Triggered = false;
    sensor2Triggered = false;
    delay(300); 
  }
  lcd.setCursor(0, 0);  // first line 
  lcd.print("visitors: ");  // show visitors 
  lcd.print(count);  // show the number beside it 
  lcd.print("   ");  // space for deleting and adding the numbers 
  if (count >= maxpeople) {  // if it reachs maxmuim number of people 
    digitalWrite(redLed, HIGH);  // so open the red light 
    digitalWrite(greenLed, LOW);  // and therefore turn off the green light 
    digitalWrite(buzzer, HIGH);  // turn on the buzzer as well
    lcd.setCursor(0, 1);  // in the second line it print 
    lcd.print("THE PLACE IS FULL!   ");  // show in the LCD warning massege  
  } 
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);  // if the maximum people not reach it return to the regular statue  turn off red light and buzzer and open the green light
    lcd.setCursor(0, 1);
    lcd.print("Status: Safe    ");  // so show in the lcd statue safe 
  }
}
```
## 🪚 How to build step-by-step
1. Get all components from the Bill of Materials (BOM) table.
2. Print the 3D structure of the project via CAD files.
3. Print the board from the PCB files, as the board relies on the microcontroller Atmega328P, which is the brain of the project.
4. Integrate the components with the circuit by connecting the LCD and the ultrasonic sensor to the pin headers.
5.	Put the ultrasonic sensor in the eye holes in the 3D design; moreover, the LCD is in the mouth of the system.
6. Link a wire between the microcontroller and a laptop, then convert the C++ code from a firmware file, and then upload the code to it.
7. Close the prototype, and it will work, showing the LCD readings. 


## 🔬 Testing Procedures
**The test plan is used to ensure the prototype's efficiency and stability through multiple tests.**
1.	After uploading the code to the microcontroller, check that the system works out and the green LED lights up to see if the prototype gets the power correctly.
2. Secondly, ensure the sensors are reading, including the ultrasonic sensor, by putting an object in front of it, and observing if it does its function.
3. Then the LCD must count the number of visitors every time an object moves forward in front of the ultrasonic sensor.
4. To ensure the Red LED and the buzzer work, try to reach the maximum number of people, then observe if the Red LED turns on and the buzzer as well.

## 🗣️ Motivation
- The motivation behind Crowd Guard comes from the fact that while I searched about the issues in Egypt, I found out that the eleven grand challenges are reducing urban congestion.
- Egypt is one of the most crowded countries in the world; moreover, the capital Cairo is ranked the 7th most crowded city in the world with its multiple metros and facilities.
- I want to make a new solution that will contribute to the comfort and consistent quality for citizens or tourists when they come to my country. 


## 💻 Project Images
### Project Structure 
<img width="550" height="453" alt="Screenshot_2026-06-10_111659-removebg-preview" src="https://github.com/user-attachments/assets/9d065d3d-5a50-4261-8d39-fc5b889cb468" />

### Board Holder 
<img width="1028" height="547" alt="84e5f9161117451d82acebd2f291468f" src="https://github.com/user-attachments/assets/b2caf262-fe3c-4bbf-ad74-ffd915961a5c" />

### Board
<img width="1045" height="537" alt="d0c6e67c37df4b7da321e62b8df305c9" src="https://github.com/user-attachments/assets/7d5a754c-ec6e-4ea2-afa4-4a4103aab16e" />

## 📄 Magizine 
<p align="center">
<img width="1398" height="2000" alt="Crowd Guard (1)" src="https://github.com/user-attachments/assets/e8145748-04ac-4547-88be-2252df8c2e56" />
</p>

## 📐 Project Files & Downloads
[3D design link](https://cad.onshape.com/documents/9b3eec702d73ff7e06d34b59/w/650e038821f09e03938fbb0c/e/957b83b2bb7a67a6845c884b)
<br>[PCB design link](https://u.easyeda.com/join?type=project&key=cdb714bca80db3ceb284dd6b91757dd1&inviter=98e19a895f66457f9303f5d792545d7f)
<br>[BOM](https://github.com/user-attachments/files/28560462/BOM.csv)



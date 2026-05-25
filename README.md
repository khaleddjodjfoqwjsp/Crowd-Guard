# Crowd-Guard

 Egypt faces several grand challenges, such as reducing urban congestion, which is one of the most crowded countries in the world, and additionally has one of the most crowded cities, which is Cairo, where it is the 7th most crowded city in the world. This issue is reflected in closed facilities, particularly metros and malls, thus it affects individuals harmfully in multiple ways, which increases accidents and even leads to death, also reduces public services badly. Since I was young, it made me upset with life, with all this crowded world, where it cannot be solved by traditional ways via workers who aren’t able to face the high number of people, thus it inspires me to look forward to addressing this issue in my country. 
 Since the first time I saw this problem, I realized that it wouldn't be solved without the power of a smart device. You can say that it was the door that made me interested in this field; fortunately, the day came to be able to address this problem with a crowd system called Crowd Guard. It is a system that detects the people who enter and leave the place using an ultrasonic sensor connected to the Arduino Uno, which is the heart of this project. The ultrasonic sensor sends waves and measures the reflected waves to determine whether there are people. It then counts them, sends the signal to the Arduino, and displays the number of people entering and exiting on the LCD. Moreover, if the number of people in the closed place exceeds the limit, it sends a signal to the buzzer to turn it on. Furthermore, there are green and red lights to display if the region is saturated with people or not, thus, it can regulate the crowd efficiently and warn people of this problem and reduce multiple accident come from crowding. Nevertheless, to ensure the project's stability, I should simulate the project in real life by creating a prototype. Firstly, it requires 3d design that can hold the components, designing it on the Onshape website as shown in Figure 1. .<img width="1080" height="771" alt="Screenshot 2026-05-24 003137" src="https://github.com/user-attachments/assets/541bb72f-9516-4160-87c6-866150d7397b" /> FIGURE 1

Even with the 3D design, it isn’t enough to make the prototype in real life, due to the Arduino and the software system, including the circuit, must be created in the TinkerCad and PCB module, which is the brain of your project and mainly the purpose of it, as shown in Figure 2 and 3.<img width="1098" height="713" alt="Screenshot 2026-05-24 003616" src="https://github.com/user-attachments/assets/9dfb8c87-6286-4e4f-aa1e-4e2b0c34a4b3" />
FIGURE 2
<img width="846" height="506" alt="Screenshot 2026-05-24 235858" src="https://github.com/user-attachments/assets/a3a77e25-f482-4112-88e5-e1789382bcc9" />
FIGURE 3

The method section. It begins with gathering the materials, then printing the 3D design that contains the components. Moreover, placing every piece in its location laterally connects the wires to the Arduino or the breadboard that links to the Arduino, as well, making the structure cleaner. If the system were applied in real life, it would be connected with electronic doors in the metros to make it affordable with the number of people.
 To conclude, crowding is a grave challenge for many regions; however, it can be solved by consuming new ideas, such as the Crowd Guard, which contributes to decreasing the crowd and returning life to closed places, such as the metro, where the crowd causes many issues, including health care disasters, inefficient public services, and improving the country's facilities even for tourists.

---

 ## 🛠️ Bill of Materials (BOM)
 
 | Component | Quantity | Price | Purchase link |
 | :--- | :---: | :--- | :--- |
 | **Arduino Uno R3** | 1 | 6.59$ | https://free-electronic.com/product/arduino-uno-r3/ |
 | **Ultrasonic sensor** | 2 | 1.51$ | https://free-electronic.com/product/ultrasonic-sensor-hc-sr04/ |
 | **Breadboard** | 2 | 0.94$ | https://free-electronic.com/product/breadboard-soldless-400-tie-points/ |
 | **LCD16 blue blacklight** | 1 | 4.90$ | https://free-electronic.com/product/lcd1604-blue-backlight/ |
 | **LED60 mixed colors** | 1 | 0.85$ | https://free-electronic.com/product/led60-mixed-color-led-size-5mm-in-box/ |
 | **65pcs jumper wires** | 1 | 0.75$ | https://free-electronic.com/product/65pcs-flexible-breadboard-jumper-wires/ |
 | **passive buzzer** | 1 | 0.47$ | https://free-electronic.com/product/passive-buzzer-module/ |  
 | **resistor** | 10 | 0.14$ | https://free-electronic.com/product/resistor-15-ohm-1w/ | 
 
---

## 🔌 Wiring Diagram & Pinouts

* **Ultrasonic sensor 1 (IN):** Trig -> Pin 5, Echo -> Pin 4
* **Ultrasonic sensor 2 (OUT):** Trig -> Pin 3, Echo -> Pin 2
* **LCD Display (16x2):** Rs -> Pin 7, E -> Pin 8, DB4 -> Pin 9, DB5 -> Pin 10, DB 6 -> Pin 11, DB7 -> Pin 12
* **Indicators:** Red LED -> A0, Green LED -> A1, Buzzer -> Pin 6

---

## 📐 Project Files & Downloads

* **CAD Model :** https://www.tinkercad.com/things/8HilV4kWgzi-dazzling-stantia-jarv/editel?returnTo=%2Fthings%2F8HilV4kWgzi-dazzling-stantia-jarv&sharecode=XAZO_gPVFohwqqy-DORh4Og6WR8cnIsBU40W7ztHvt8
* 
* **3D CAD Model :** https://cad.onshape.com/documents/caed0649f48957575ee98a36/w/9fba59ddc9e91909b82d6cf2/e/f387e753fe8c654746c10a25
* 
* **Bill of Materials (BOM List):** [BOM.csv](https://github.com/user-attachments/files/28216923/BOM.csv)
* 
* **Arduino Code:** 

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

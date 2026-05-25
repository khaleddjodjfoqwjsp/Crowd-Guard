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

/*
 * Follow On The Track
 * BASE CODE
 * 
 * Author: Nate Krauss
 */

#include <DriveSys.h>
#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

//ultrasonic
const int trigPin = 13;
const int echoPin = 12;
float duration, distance;
//smoothing variables
const int readingSampleSize = 10;
int readings[readingSampleSize];      // the readings from the analog input
int readingIndex = 0;              // the index of the current reading
int readingTotal = 0;                  // the running total
int readingAverage = 0;                // the average
int ignore = 0;

DriveSys  DriveSys;

void setup() {
  Wire.begin();
  t = 0;

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int thisReading = 0; thisReading < readingSampleSize; thisReading++) {
    readings[thisReading] = 0;
  }
  
  Serial.begin(9600);  
  Serial.println("SERIAL MONITOR ENABLED");
}

void updateArray() {
  Wire.requestFrom(9, 16);
  while (Wire.available()) { 
    data[t] = Wire.read();
    if (t < 15) {
      t++;
    } else {
      t = 0;
    }
  }
}

void updateUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration / 2) * 0.0343;
}

void smoothingUltrasonic() {
  updateUltrasonic();
  readingTotal = readingTotal - readings[readingIndex];
  readings[readingIndex] = distance;
  readingTotal = readingTotal + readings[readingIndex];
  readingIndex = readingIndex + 1;
  if (readingIndex >= readingSampleSize) {
    readingIndex = 0;
  }
  readingAverage = readingTotal / readingSampleSize;
  delay(1);
}

void lineFollow() {
  if (ignore < 1000 || readingAverage >= 23) { //when leader robot is not seen
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      DriveSys.rightControl(0,0);
      DriveSys.leftControl(0,0);
    } else if (data[14] < 40) {
      DriveSys.rightControl(0,150);
      DriveSys.leftControl(0,150);
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      DriveSys.rightControl(0,175);
      DriveSys.leftControl(0,25);
    } else {
      DriveSys.rightControl(0,25);
      DriveSys.leftControl(0,125);
    }
  } else if (10 < readingAverage < 23) { //when leader robot is being sensed 
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      DriveSys.rightControl(0,0);
      DriveSys.leftControl(0,0);
    } else if (data[14] < 40) {
      DriveSys.rightControl(0,map(readingAverage, 10, 23, 0, 150));
      DriveSys.leftControl(0,map(readingAverage, 10, 23, 0, 150));
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      DriveSys.rightControl(0,map(readingAverage, 10, 23, 0, 175)); 
      DriveSys.leftControl(0,map(readingAverage, 10, 23, 0, 25));
    } else {
      DriveSys.rightControl(0,map(readingAverage, 10, 23, 0, 25));
      DriveSys.leftControl(0,map(readingAverage, 10, 23, 0, 125));
    }
  } else if (readingAverage < 10) {
    DriveSys.rightControl(0,0);
    DriveSys.leftControl(0,0); 
  }
}

void sensorDataPrint() {
  /*Serial.print("data[0]:");
  Serial.println(data[0]);
  Serial.print("data[2]:");
  Serial.println(data[2]);
  Serial.print("data[4]:");
  Serial.println(data[4]);
  Serial.print("data[6]:");
  Serial.println(data[6]);
  Serial.print("data[8]:");
  Serial.println(data[8]);
  Serial.print("data[10]:");
  Serial.println(data[10]);
  Serial.print("data[12]:");
  Serial.println(data[12]);
  Serial.print("data[14]:");
  Serial.println(data[14]);*/

  Serial.print("SMOOTHING: ");
  Serial.print(readingAverage);
  Serial.print("   //   INSTANT: ");
  Serial.println(distance);

  //Serial.println(ignore);
  
  //delay(500);
}

void loop() {
  updateArray();
  smoothingUltrasonic();
  lineFollow();
  
  //sensorDataPrint();
  ignore++;
}

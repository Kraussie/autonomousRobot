/*
 * Follow On The Track
 * BASE CODE
 * 
 * Author: Nate Krauss
 */

#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];

//motor LEFT
int enA = 11;
int in1 = 5;
int in2 = 6;
//motor RIGHT
int enB = 3;
int in3 = 10;
int in4 = 9;
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

void setup() {
  Wire.begin();
  t = 0;

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT); 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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

void leftControl(int left_direction, int left_speed) { //function to simplify controlling of motors; forward = 0, backward = 1
  if (left_direction == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (left_direction == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(enA, left_speed); //speed control, min = 0, max = 255
}

void rightControl(int right_direction, int right_speed) { //function to simplify controlling of motors; forward = 0, backward = 1
  if (right_direction == 0) { 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (right_direction == 1) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  analogWrite(enB, right_speed); //speed control, min = 0, max = 255
}

void lineFollow() {
  if (ignore < 1000 || readingAverage >= 17) { //when leader robot is not seen
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      rightControl(0,0);
      leftControl(0,0);
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      rightControl(0,200);
      leftControl(0,50);
    } else if (data[14] < 40) {
      rightControl(0,200);
      leftControl(0,200);
    } else {
      rightControl(0,50);
      leftControl(0,125);
    }
  } else if (readingAverage < 17) { //when leader robot is being sensed to be close
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      rightControl(0,0);
      leftControl(0,0);
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      rightControl(0,150); 
      leftControl(0,50);
    } else if (data[14] < 40) {
      rightControl(0,map(readingAverage, 4, 17, 0, 200));
      leftControl(0,map(readingAverage, 4, 17, 0, 200));
    } else {
      rightControl(0,50);
      leftControl(0,125);
    }
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
  
  sensorDataPrint();
  ignore++;
}

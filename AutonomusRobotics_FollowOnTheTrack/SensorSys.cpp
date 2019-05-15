#include "Arduino.h"
#include "SensorSys.h"

SensorSys::SensorSys(int trigPin, int echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int thisReading = 0; thisReading < readingSampleSize; thisReading++) {
    readings[thisReading] = 0;
  }
}

void SensorSys::updateUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = (duration / 2) * 0.0343;
}

void SensorSys::smoothingUltrasonicSensor() {
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

void SensorSys::printUltrasonic(); {
  Serial.print("SMOOTHING: ");
  Serial.print(readingAverage);
  Serial.print("   //   INSTANT: ");
  Serial.println(distance);
}

void SensorSys::updateLineFollower() {
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

void SensorSys::printLineFollower() {
  Serial.print("data[0]:");
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
  Serial.println(data[14]);
}

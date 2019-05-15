#include "Arduino.h"
#include "DriveSys.h"

DriveSys::DriveSys() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT); 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void DriveSys::leftControl(int left_direction, int left_speed) {
  if (left_direction == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (left_direction == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(enA, left_speed); //speed control, min = 0, max = 255
}

void DriveSys::rightControl(int right_direction, int right_speed) {
  if (right_direction == 0) { 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (right_direction == 1) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  analogWrite(enB, right_speed); //speed control, min = 0, max = 255
}

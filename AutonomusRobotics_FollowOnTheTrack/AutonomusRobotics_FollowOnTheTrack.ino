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

int ignore = 0;

void setup() {
  Wire.begin();
  t = 0;
  
  Serial.begin(9600);  
  Serial.println("SERIAL MONITOR ENABLED");
}

void lineFollow() {
  if (ignore < 1000 || readingAverage >= 23) { //when leader robot is not seen
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      rightControl(0,0);
      leftControl(0,0);
    } else if (data[14] < 40) {
      rightControl(0,150);
      leftControl(0,150);
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      rightControl(0,175);
      leftControl(0,25);
    } else {
      rightControl(0,25);
      leftControl(0,125);
    }
  } else if (10 < readingAverage < 23) { //when leader robot is being sensed 
    if (data[0] < 40 && data[14] < 40) { //when line follower sensor only sees black
      rightControl(0,0);
      leftControl(0,0);
    } else if (data[14] < 40) {
      rightControl(0,map(readingAverage, 10, 23, 0, 150));
      leftControl(0,map(readingAverage, 10, 23, 0, 150));
    } else if (data[0] < 40 || data[2] < 40 || data[4] < 40 || data[6] < 40 || data[8] < 40 || data[10] < 40 || data[12] < 40) {
      rightControl(0,map(readingAverage, 10, 23, 0, 175)); 
      leftControl(0,map(readingAverage, 10, 23, 0, 25));
    } else {
      rightControl(0,map(readingAverage, 10, 23, 0, 25));
      leftControl(0,map(readingAverage, 10, 23, 0, 125));
    }
  } else if (readingAverage < 10) {
    rightControl(0,0);
    leftControl(0,0); 
  }
}

void loop() {
  lineFollow();
  
  ignore++;
}

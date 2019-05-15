#ifndef DriveSys_h
#define DriveSys_h

#include "Arduino.h"

class DriveSys {
  public:
    DriveSys();
    void leftControl(int left_direction, int left_speed);
    void rightControl(int right_direction, int right_speed);
    //motor LEFT
    int enA = 11;
    int in1 = 5;
    int in2 = 6;
    //motor RIGHT
    int enB = 3;
    int in3 = 10;
    int in4 = 9;
  private:
};

#endif

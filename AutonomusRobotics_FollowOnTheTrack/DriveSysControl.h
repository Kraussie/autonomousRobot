#ifndef DriveSysControl_h //if DriveSysControl library has never been defined before
#define DriveSysControl_h

#include "Arduino.h"

class DriveSysControl {
  public:
    //constructor method, i.e. setup for the library
    DriveSysControl(int enA = 11, int in1 = 5, int in2 = 6, int enB = 3, int in3 = 10, int in4 = 9);

    //library functions
    void leftControl(int left_direction, int left_speed);
    void rightControl(int right_direction, int right_speed);
  private:
};

#endif

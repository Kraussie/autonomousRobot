#ifndef DriveSysControl_h //if DriveSysControl library has never been defined before
#define DriveSysControl_h

#include "Arduino.h"

class DriveSysControl_h {
  public:
    //constructor method, i.e. setup for the library
    DriveSysControl(int enA, int in1, int in2, int enB, int in3, int in4);

    //library functions
    void leftControl();
    void rightControl();
  private:
}

#endif

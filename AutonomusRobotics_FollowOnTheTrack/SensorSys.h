#ifndef SensorSys_h //if DriveSysControl library has never been defined before
#define SensorSys_h

#include "Arduino.h"

class SensorSys {
  public:
    //constructor method, i.e. setup for the library
    SensorSys(int trigPin=13, int echoPin=12);
    float duration, distance;

    //library functions
    void updateUltrasonic();
    void smoothingUltrasonic();
    void printUltrasonic();
    void updateLineFollower();
    void printLineFollower();
  private:
};

#endif

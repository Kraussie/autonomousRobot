#ifndef SensorSys_h //if DriveSysControl library has never been defined before
#define SensorSys_h

#include "Arduino.h"

class SensorSys {
  public:
    //constructor method, i.e. setup for the library
    SensorSys(int trigPin=13, int echoPin=12);
    float duration, distance;
    int readingSampleSize = 10;
    int readings[readingSampleSize];      // the readings from the analog input 
    int readingIndex = 0;              // the index of the current reading
    int readingTotal = 0;                  // the running total
    int readingAverage = 0;                // the average

    //library functions
    void updateUltrasonic();
    void smoothingUltrasonic();
    void printUltrasonic();
    void updateLineFollower();
    void printLineFollower();
  private:
};

#endif

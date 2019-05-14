#ifndef SensorSys_h //if DriveSysControl library has never been defined before
#define SensorSys_h

class SensorSys_h {
  public:
    //constructor method, i.e. setup for the library
    SensorSys(const int trigPin, const int echoPin, float duration, float distance, const int readingSampleSize = 10, int readings[readingSampleSize], int readingIndex = 0, int readingTotal = 0, int readingAverage)

    //library functions
    void updateUltrasonic();
    void smoothingUltrasonic();
    void printUltrasonic();
    void updateLineFollower();
    void printLineFollower();
  private:
}

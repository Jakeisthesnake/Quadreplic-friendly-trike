#include <Arduino.h>

#ifndef TRIKE_THROTTLE
#define TRIKE_THROTTLE

#define THROTTLE_PIN 13
#define MIDDLE_THROTTLE 1
#define SIDE 2
#define VERY_SIDE 3
#define TOO_FAR_SIDE 4
#define CS 53


class Throttle{
public:
  int throttleVal; //output from 0-200
  int tPin;
  unsigned long throttleEventClock;
  int throttlePWM;
  int zone;
  int steerCenter;
  int maxThrottle;
  int steerPos;
  uint8_t address;
  
  Throttle(int tPin);
  void applyThrottle(int tVal, unsigned long timer, float velocity, bool EBrakeInput);
  void goFaster(unsigned long timer);
  int digitalPotWrite(int value);
};

#endif


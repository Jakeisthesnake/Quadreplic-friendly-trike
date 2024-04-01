#include <Arduino.h>

#ifndef EBRAKE_H
#define EBRAKE_H

#define EBRAKE_PIN 2
#define EBRAKE_GROUND_PIN 23


class EBrake{
public:
  int EPin;
  int GPin;
  bool EStop;
  // for FSR
   int flexiForcePin;
  int forceThreshold;
  // for accelerometer
  int groundpin;
  int powerpin;
  int xpin;
	int ypin;
	int zpin;
	int prevX; //store previous X value. Use to detect change in analog reading of accelerometer
	int prevY;
	int prevZ;

  int initialForce;
  
  EBrake(int EBrakePin, int EBrakeGroundPin);
  void CheckEBrake();
};

#endif

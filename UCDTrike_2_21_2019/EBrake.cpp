#include "EBrake.h"
#include <Arduino.h>

//set function Velocity as part of the Velocity class
EBrake::EBrake(int EBrakePin, int EBrakeGroundPin){
  EPin = EBrakePin;
  GPin = EBrakeGroundPin;
  pinMode(EPin, INPUT);
  digitalWrite(EPin, INPUT_PULLUP);
  pinMode(GPin, OUTPUT);
  digitalWrite(GPin, LOW);
  EStop = 0;
  // for FSR
  flexiForcePin = A8; //needs to redefine the input to match up
  forceThreshold = -100; // based on data gathered from FSR
  // for accelerometer
  groundpin = 18;             // analog input pin 4 -- ground
  powerpin = 19;              // analog input pin 5 -- voltage
  xpin = A10;                 // x-axis of the accelerometer. can be changed later
  ypin = A11;                 // y-axis
  zpin = A12;                  // z-axis
  prevX = -1; //No read is less tha 0, so this can be used to verify whether there is a stored value.
  prevY = -1;
  prevZ = -1;
  
  initialForce = -1;
}

void EBrake::CheckEBrake(){
 
};


#include "Velocity.h"
#include <Arduino.h>

//set function Velocity as part of the Velocity class
Velocity::Velocity(int VelocityPin, int GroundPin){
  VPin = VelocityPin;
  GPin = GroundPin;
  lastVelocityTime = 0;
  WheelSpeed = 0.0;
  speedConstant = 1*3.14159*26/63360*3600000; //secant of wheel circumference in mile: deltaTicks[ticks]/deltaTime[msec] * (1 rev/4ticks) * (26pi in/rev) * (1 mil/63360 in) * (3,600,000 msec/hour)= tick* (miles msec/tick hour) = speed in mph
  pinMode(VPin, INPUT);
  digitalWrite(VPin, INPUT_PULLUP);
  pinMode(GPin, OUTPUT);
  digitalWrite(GPin, LOW);
  
};

void Velocity::getSpeed(unsigned long velocityTimer){
  VState = digitalRead(VPin);
  VelocityTimer = millis();
//  Serial.print("VState = ");
//  Serial.println(VState);
//  Serial.print("SwitchState = ");
//  Serial.println(SwitchState);
//  Serial.print("dTime = ");
//  Serial.println(VelocityTimer - (lastVelocityTime + 100));
//  Serial.print("rotationTicks = ");
//  Serial.println(rotationTicks);
  if ((VState == LOW) && (SwitchState != VState) && (lastVelocityTime + 100 < VelocityTimer)){
    rotationTicks ++;
    deltaTime = (velocityTimer - lastVelocityTime); // what is the time since the last tick? 1 ms * (1 sec/1000 ms) * (1 min/60 sec) * (1 hr/60 min)
//    Serial.print("deltaTime = ");
//    Serial.println(deltaTime);
    deltaTicks = (rotationTicks - lastTicksCount); // how much distance, based on ticks, has been traveled
//    Serial.print("deltaDistance = ");
//    Serial.println(deltaDistance);
    WheelSpeed = deltaTicks/deltaTime*speedConstant; // velocity = distance / time
    lastTicksCount = rotationTicks; // update rotation ticks
    lastVelocityTime = VelocityTimer;
    }
  SwitchState = VState;

  if ((VelocityTimer - lastVelocityTime > deltaTime) && (deltaTime > 0)){
    WheelSpeed = 1160.0/(VelocityTimer - lastVelocityTime); //add 1 since at the beginning, deltaTime = 0
  }
//  WheelSpeed = 0; // uncomment if velocity sensor doesn't work
//  Serial.print("wheelspeed = ");
//  Serial.println(WheelSpeed);
//  Serial.print("VelocityTimer = ");
//  Serial.println(VelocityTimer);
//  Serial.print("last velocity time = ");
//  Serial.println(lastVelocityTime);
//  Serial.println();
};

//mph = ((#ticks)*.00032229*3600000)//(dT)
//mile/hour - >rev /sec:    1mile/hour *  hour/3600sec * 63360 in / mile * 1 rev/26pi sec

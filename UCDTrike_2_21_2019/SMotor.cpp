//libraries

#include "SMotor.h"
#include <Arduino.h>

using namespace std;

//set function SMotor as part of the SMotor class
SMotor::SMotor(int sPin_a, int sPin_b, int SteerPotPin, int SteerCurrentPin, int EnablePin){
  onPin = EnablePin;
  speedPin_a = sPin_a;
  speedPin_b = sPin_b;
  SPotPin = SteerPotPin;
  SCurrentPin = SteerCurrentPin;
  pinMode(SPotPin, INPUT);
  pinMode(speedPin_a, OUTPUT);
  pinMode(speedPin_b, OUTPUT);
  pinMode(onPin, OUTPUT);
  analogWrite(speedPin_a, 0);
  analogWrite(speedPin_b, 0);
  digitalWrite(onPin, HIGH);
  eventClock = 0;
  turnSpeed = 20;
  ETurnSpeed = 40;
  maxTurnSpeed = 50;
  steerCenter = 860;
  turnedTooFar = 1;
  eventDelay = 250;
};

void SMotor::turnHarder(unsigned long timer){
  float ratio = (timer - eventClock) / eventDelay; //set ratio to be percent of amount of 500 ms passed
  turnSpeed = max(15 * ratio, turnSpeed); //increase power of brake accordingly with 
//  eventClock = timer; // reset the brake event clock because the strength was just incresed
  if (turnSpeed > maxTurnSpeed){
    turnSpeed = maxTurnSpeed;
  }
};

//declare function goToPos under SMotor class. The function is expected to return no info.
void SMotor::goToPos(int setPos, unsigned long timer, float velocity, bool EBrakeInput){
//  Serial.print("velocity  ");
//  Serial.println(velocity);
//  Serial.print("LR steer ");
//  Serial.println(setPos);
//  Serial.print("Turn Speed ");
//  Serial.println(turnSpeed);
//  Serial.print("Event clock ");
//  Serial.println(eventClock);
//  Serial.println("");

  steerPos = analogRead(SPotPin);
//  steerPos = 762; // for debugging when no sensors attached
  
      //check what zone the steering is in
    Serial.print("steer pot  ");
    Serial.println(steerPos);

//  if (velocity < 6) {
//    turnLimit = 50;
//  }
//  else {
//    turnLimit = 10*(-sqrt(velocity - 6) + 5);
//  }
//
//  if (velocity > 10) {
//    maxTurnPower = 20;
//  }
//  else if (velocity > 2) {
//    maxTurnPower = 50 - (velocity-2)/(10-2)*30;
//  }
//  else {
//    maxTurnPower = 50;
//  }
  
 
  //if Quadstick x-axis position is on the left (center is 128)
    //Serial.print(SCurrentPin); // debuggung
    //Serial.println(setPos); //debuggung
  if ((setPos < 108) && (setPos =! 0)){ // is the quadstick turned to the left?
    speedPin = speedPin_b; //set A motor driver as positive to turn CCW which corresponds to a right turn
    groundPin = speedPin_a; //set B motor driver as ground to turn CCW which corresponds to a right turn
    if (steerPos < steerCenter +50){
      turnHarder(timer);
      analogWrite(groundPin, 0);
      analogWrite(speedPin, turnSpeed);
    }
    else{
      analogWrite(groundPin, 0);
      analogWrite(speedPin, 0);
    }
  }

  else if(setPos > 148){ // is the quadstick turned to the right?
//    Serial.println("I wanna go right");
    speedPin = speedPin_a; //set B motor driver as positive to turn CW which corresponds to a left turn
    groundPin = speedPin_b; //set A motor driver as ground to turn CW which corresponds to a left turn
    if (steerPos > steerCenter - 50){
      turnHarder(timer);
      analogWrite(groundPin, 0);
      analogWrite(speedPin, turnSpeed);
    }
    else{
      analogWrite(groundPin, 0);
      analogWrite(speedPin, 0);
    }
  }
  
  else{
    SPotVal = analogRead(SPotPin);
//    SPotVal = 586; // for debugging when no sensors attached
//    Serial.print("SpotVal = ");
//    Serial.println(SPotVal);
//    Serial.print("steerCenter = ");
//    Serial.println(steerCenter);
    if (SPotVal > steerCenter + 1){ //if sensed wheels are turned to the left (center is 165)
      speedPin = speedPin_a; //set B motor driver as positive to turn CW which corresponds to a left turn
      groundPin = speedPin_b; //set A motor driver as ground to turn CW which corresponds to a left turn
      turnHarder(timer);
      analogWrite(groundPin, 0);  //set ground pin to 0
      analogWrite(speedPin, turnSpeed);
//      Serial.println("off the the left");
    }
    else if (SPotVal < steerCenter - 1){ //if sensed wheels are turned to the right (center is 165)
      speedPin = speedPin_b; //set A motor driver as positive to turn CCW which corresponds to a right turn
      groundPin = speedPin_a; //set B motor driver as ground to turn CCW which corresponds to a right turn
      turnHarder(timer);
      analogWrite(groundPin, 0);  //set ground pin to 0
      analogWrite(speedPin, turnSpeed);
//      Serial.println("off the the right");
    }
    else{
      analogWrite(groundPin, 0);  //set ground pin to 0
      analogWrite(speedPin, 0); //stop the steering motor 
      turnSpeed = 20;
//      Serial.println("Just chilling");
    }
    eventClock = timer; // let keep the event time updated to what is happening, the motor will start at a default of 20 PWM
  } 
    
    

//      
//  //  every .01 seconds, check if steering motor are running to much current:
//  if (currentCounter + 10 > timer){
//    for (i = 0; i < (NUM_STEER_CURRENT_SAMPLES-1); i ++){ // loop though each data point
//      currentData[i] = currentData[i+1]; //shift each data back one slot
//      totalCurrent = totalCurrent + currentData[i]; // add each data poin to the sum
//    }
//    currentData[NUM_STEER_CURRENT_SAMPLES-1] = analogRead(SCurrentPin); // 40mV/A for the sensor 
//    totalCurrent = totalCurrent + currentData[NUM_STEER_CURRENT_SAMPLES-1];
//    //Serial.print(""); //debugging
//    currentCurrent = totalCurrent / NUM_STEER_CURRENT_SAMPLES; // take average of current values
//    //Serial.println(currentCurrent); // debugging
//
//    currentCurrentsTotal = currentCurrentsTotal - currentsForAverage[0];
//    for (j = 0; j < NUM_STEER_CURRENTS_FOR_AVERAGE; j++){
//      currentsForAverage[j] = currentsForAverage[j+1];
//    }
//    currentsForAverage[NUM_STEER_CURRENTS_FOR_AVERAGE] = currentCurrent;  
//    currentCurrentsTotal = currentCurrentsTotal + currentCurrent;
//    currentAverage = currentCurrentsTotal/NUM_STEER_CURRENTS_FOR_AVERAGE;
//  
//    if (currentAverage > maxCurrent){
//      maxTurnSpeed = maxTurnSpeed - 10;
//    }
//    else{
//      maxTurnSpeed = 60;
//    }

//    Serial.print("turnsppeed = ");
//    Serial.println(turnSpeed);
//  }

};

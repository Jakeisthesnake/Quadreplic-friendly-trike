//libraries
#include "Throttle.h"
//#include <Arduino.h>
#include <SPI.h>

//set function Throttle as part of the Throttle class
Throttle::Throttle(int pinNum){
  throttleVal = 0; //initially no speed
  tPin = pinNum;
  throttleEventClock = 0;
  throttlePWM = 10;
  steerCenter = 860;
  maxThrottle = 160;
  address = 0x00;
};

void Throttle::goFaster(unsigned long timer){
  float ratio = (timer - throttleEventClock) / 500.0; //set ratio to be percent of amount of 500 ms passed
  //Serial.println(timer);
  //Serial.println(throttleEventClock);
  throttlePWM = max(15 * ratio,throttlePWM); //increase power of brake accordingly with 
  // throttleEventClock = timer; // reset the brake event clock because the strength was just incresed
  if (throttlePWM > maxThrottle)
    throttlePWM = maxThrottle;
};

int Throttle::digitalPotWrite(int value){
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
//  Serial.print("value = ");
//  Serial.println(value);
  };

//declare function goToPos under SMotor class. The function is expected to return no info.
void Throttle::applyThrottle(int tVal, unsigned long timer, float velocity, bool EBrakeInput){

  if(EBrakeInput == 1){
    digitalPotWrite(0); //stop the throttle
//    Serial.println("Ebrake on :(");
  }

  else{
//    Serial.println("Ebrake off :D");
    //check what zone the steering is in
    steerPos = analogRead(A2);
    if ((steerPos > steerCenter - 10) && (steerPos < steerCenter + 10)){
      zone = MIDDLE_THROTTLE;
    }
    else if ((steerPos > steerCenter - 30) && (steerPos < steerCenter + 30)){
      zone = SIDE;
    }
    else if ((steerPos > steerCenter - 50) && (steerPos < steerCenter + 50)){
      zone = VERY_SIDE;
    }   
    else {
      zone = TOO_FAR_SIDE;
    }   
//     Serial.print("throttle Zone: ");
//     Serial.println(zone); 
//    Serial.print("Vel: ");
//    Serial.println(velocity);
    //if Quadstick y-axis position up (center is 128)
//    Serial.print("tVal = ");
//    Serial.println(tVal);
    if (tVal < 90){ // is the quadstick turned upt?
      switch (zone){
        case MIDDLE_THROTTLE:
//          Serial.println("middle");
          if (velocity < 30){
            goFaster(timer);
          }
          else{
            throttlePWM = 0;
          }
          break;
        case SIDE:
//          Serial.println("side");
          if (velocity < 7){
            goFaster(timer);
          }
          else{
            throttlePWM = 0;
          }
          break;
        case VERY_SIDE:
//          Serial.println("very side");
          if (velocity < 3){
            goFaster(timer);
          }
          else{
            throttlePWM = 0;
          }
          break;
        case TOO_FAR_SIDE:
//          Serial.println("too far side");
          if (velocity < 1){
            goFaster(timer);
          }
          else{
            throttlePWM = 0;
          }
      }
//      Serial.print("gimme speed : ");
//      Serial.println(throttlePWM);  
      digitalPotWrite(throttlePWM); // tell to motor to turn at the PWM that made it through the above decision tree
    }
  
    //if Quadstick y-axis position is not up
    else { // user doesn't want to speed
      digitalPotWrite(0); //stop the throttle
      throttlePWM = 10; // set throttle PWM back to a low power
      throttleEventClock = timer; // let's keep the event time updated to what is happening,
      //the throttle will start at a default of 65 PWM
//      Serial.println(4);
    }
  }
//   Serial.print("TVal: ");
//   Serial.println(tVal);  
//   Serial.print("Throttle: ");
//   Serial.println(throttlePWM) ;
};


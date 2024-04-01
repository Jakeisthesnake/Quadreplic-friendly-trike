#include "BMotor.h"
#include <Arduino.h>

//set function BMotor as part of the BMotor class
BMotor::BMotor(int dPin, int sPin, int BrakePotPin, bool brakeDirection, int brakeCurrentPin, int BrakePotCenter){
  dirPin = dPin; // pin that contrls the direction of the motor driver
  speedPin = sPin; // pin that controls the PWN of the motor driver
  currentPin = brakeCurrentPin; // pin that receives current sensor measurements
  BPotPin = BrakePotPin; // pin that recives info from the potentiometer associated with the displacement of the potentiometer.
  brakeEventClock = 0; // a counter to keep track of how long the user has been doing domthing
  noInputTimer = 0; // a counter to keep track of when the last time the user moved the quadstick
  noInputDelay = 100000; // the time to wait while the user does nothing
  BrakePWM = 20 ; // initial value of starting BM
  maxEBrakePWM = 50; // as high as the arduino can go?
  maxBrakePWM = 50; // max brake strength while keeping int account of the limits of the current
  PotCenter = BrakePotCenter; // value at vhich the brake potentiometer is centered
  pinMode(BPotPin, INPUT); // setting the potentiometer pin as an input pin
  analogWrite(speedPin, 0); //making sure that the brake are initally not moving
  if (brakeDirection){ // brakes can have direction specified when they are declare
    tightenPWM = 255; 
    loosenPWM = 0;
  }
  else {
    tightenPWM = 0;
    loosenPWM = 255;
  }
};


void BMotor::brakeHarder(unsigned long timer){
  float ratio = 40*(timer - brakeEventClock) / 1000; //set ratio to be percent of amount of 500 ms passed
  BrakePWM = max(ratio, BrakePWM); //increase power of brake accordingly with 
//  brakeEventClock = timer; // reset the brake event clock because the strength was just incresed
  if (BrakePWM > maxEBrakePWM){
    BrakePWM = maxEBrakePWM;
  }
//  Serial.print("BrakePWM = ");
//  Serial.println(BrakePWM);
};

//declare function setBrake under BMotor class. The function is expected to return no info.
void BMotor::setBrake(int setPos, int XPos, unsigned long timer, float velocity, bool EBrakeInput){  // sets the value and direction of the PWM signal to the motor of the brake motor
  // chekc e-brake, if triggered, increase brakes at set rate until velocity = 0
  if (EBrakeInput == 1){ // is an emergency stop called? if yes, do the following:
    analogWrite(dirPin, tightenPWM); // set direction of brakes to tighten
    if (velocity >= 1){ // if the trike is moving and .5 second since the strength to the brakes has been called: do the following
      brakeHarder(timer); //call function to tighten brake gradually
    }
    analogWrite(speedPin, BrakePWM); // set pwn to motor
//    Serial.println("ebrake is on"); // degbugging
  }
  else{ //no emergency brake, so carry on as normal
    if (setPos > 135 || velocity > 10) { // is the QS pointed down or is the velocity greater than 10?
      if (velocity > 10){
        
      }
      brakeHarder(timer);
      analogWrite(dirPin, tightenPWM); // set direction
      analogWrite(speedPin, BrakePWM); // set pwn to motor
//      Serial.println("brake is on"); // degbugging
    }
    
    else{ // if the QS isn't pointed down or to the side and the trike is going less than 10 mph:
      if(noInputTimer + noInputDelay < timer){ // if there hasn't been input for 1 second, close the breaks
        brakeHarder(timer);
        analogWrite(dirPin, tightenPWM); // set direction
        analogWrite(speedPin, BrakePWM); // set pwn to motor
//        Serial.println("Nothing happened, so squeezing brake");
      }
      else{
        BPotVal = analogRead(BPotPin);
//        Serial.print("BPotVal = ");
//        Serial.println(BPotVal);
//        BPotVal = PotCenter; //uncomment when debugging without breakpot sensor
        if (BPotVal < PotCenter-5){ //if sensed brake is turned to the left 
          analogWrite(dirPin, 255); //set direction to CW to recenter, don't use tightenPWM and loosenPWM because potentiometers are soldered on the same way.
          analogWrite(speedPin, 20);
//          Serial.println("brake is uncentered left"); // degbugging
        }
        else if (BPotVal > PotCenter+5){ //if sensed brake is turned to the right 
          analogWrite(dirPin, 0); //set direction to CCW to recenter, don't use tightenPWM and loosenPWM because potentiometers are soldered on the same way.
          analogWrite(speedPin, 20);
//          Serial.println("brake is uncetered right"); // degbugging
        }
        else{
          analogWrite(speedPin, 0); //stop the steering motor
          BrakePWM = 20; // reset the BrakePWM.
          brakeEventClock = timer; // keep event clock updated so that when something checks the event clock it reads that nothing new has happened.
//          Serial.println("brake is centered"); // degbugging
        }
//        Serial.println("open those brakes");
      }
    }
    if ((XPos < 124) || (132 < XPos) || (setPos < 124) || (132 < setPos)){ // the qs is not in the middle  (small range 124-132 incase the user is slowly turning it)
      noInputTimer = timer;
//      Serial.print("No input");
    }
  }

//
//  //  every .01 seconds, check if brake motors are running to much current:
//  if (currentCounter + 10 > timer){
//    for (i = 0; i < (NUM_BRAKE_CURRENT_SAMPLES-1); i ++){ // loop though each data point
//      currentData[i] = currentData[i+1]; //shift each data back one slot
//      totalCurrent = totalCurrent + currentData[i]; // add each data poin to the sum
//    }
//    currentData[NUM_BRAKE_CURRENT_SAMPLES-1] = analogRead(currentPin); // 40mV/A for the sensor 
//    totalCurrent = totalCurrent + currentData[NUM_BRAKE_CURRENT_SAMPLES-1];
//    //Serial.print(""); //debugging
//    currentCurrent = totalCurrent / NUM_BRAKE_CURRENT_SAMPLES; // take average of current values
//    //Serial.println(currentCurrent); // debugging
//
//    currentCurrentsTotal = currentCurrentsTotal - currentsForAverage[0];
//    for (j = 0; j < NUM_BRAKE_CURRENTS_FOR_AVERAGE; j++){
//      currentsForAverage[j] = currentsForAverage[j+1];
//    }
//    currentsForAverage[NUM_BRAKE_CURRENTS_FOR_AVERAGE] = currentCurrent;  
//    currentCurrentsTotal = currentCurrentsTotal + currentCurrent;
//    currentAverage = currentCurrentsTotal/NUM_BRAKE_CURRENTS_FOR_AVERAGE;
//  
//    if (currentAverage > maxCurrent){
//      maxBrakePWM = maxBrakePWM - 10;
//    }
//    else{
//      maxBrakePWM = 100;
//    }
//  }
//  Serial.print("tighten pwm  ");
//  Serial.println(tightenPWM);


};

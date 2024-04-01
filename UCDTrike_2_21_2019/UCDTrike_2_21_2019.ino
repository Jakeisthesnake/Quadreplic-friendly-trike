//libraries
#include <SPI.h>
#include "PS3USB.h"
#include "BMotor.h"
#include "SMotor.h"
#include "coord.h"
#include "Throttle.h"
#include "Velocity.h"
#include "EBrake.h"
#include "RCcoord.h"

unsigned long universalTimer;
int RCon;

USB     Usb; //create USB object
PS3USB  QS(&Usb); //create Quadstick object
coord   Where(&Usb); //create coordination object 
SMotor  steer(STEER_PWM_A, STEER_PWM_B, STEER_POT, STEER_CURRENT_SENSOR, ENABLE_PIN); //create steering object
BMotor  BrakeR(BRAKER_DIR, BRAKER_PWM, BRAKER_POT, BRAKE_SPINS_RIGHT, BRAKER_CURRENT_PIN, BRAKER_POT_CENTER);
BMotor  BrakeL(BRAKEL_DIR, BRAKEL_PWM, BRAKEL_POT, BRAKE_SPINS_LEFT, BRAKEL_CURRENT_PIN, BRAKEL_POT_CENTER);
Throttle Go(THROTTLE_PIN);
Velocity VSensor(VELOCITY_PIN, GROUND_PIN);
EBrake   StopNow(EBRAKE_PIN, EBRAKE_GROUND_PIN); //Get rid of this! (Pressure sensor and accelerometer)
RCcoord rc(&Where, &StopNow);

int checkmeter = 20;
int RCTicker = 0;
unsigned long check1 = 0;
unsigned long check2 = 0;
unsigned long check3 = 0;
unsigned long check4 = 0;
void setup() {
  //put your setup code here, to run once:
  Serial.begin(115200); //set data rate to 115200 bits/sec for serial data transmission
//  Serial.println("Hello world");
 
  pinMode (CS, OUTPUT); // for throttle digital pot
  SPI.begin(); // for throttle digital pot
}


void loop() { 
  checkmeter = checkmeter + 1;
  RCTicker = RCTicker + 1;
  if (RCTicker == 200){
    RCTicker = 0;
    check1 = millis();
//    Serial.println(millis());
    RCon = rc.checkRC();  // comment out when debugging without the rc plugged in
//    RCon = 0; // for debugging without the rc plugged in
//    Serial.print("Rcon: ");
//    Serial.println(RCon);
    rc.checkRCEBrake(); // comment out when debugging without the rc plugged in
    StopNow.CheckEBrake();
    if (RCon == 1) rc.getCoord(); // comment out when debugging without the rc plugged in
    check2 = millis();
  }

//  if (RCon == 1) Serial.println("RC on");
  if (RCon == 0) Where.getPos(Usb, QS); //get position from the Quadstick
//  if (RCon == 0) Serial.println("RC off");
//  Serial.print("EStop: ");
//  Serial.println(StopNow.EStop);
  universalTimer = millis(); // updates clock that functions use
  VSensor.getSpeed(universalTimer); // change the public variable "WheelSpeed" of VSensor 
  BrakeR.setBrake(Where.UD, Where.LR, universalTimer, VSensor.WheelSpeed, StopNow.EStop); // determined whether to squeeze brake based on whether the user if doing anything (LR,UD) not = (128,128), what the trike speed is and if the ebrake has been triggered.
  BrakeL.setBrake(Where.UD, Where.LR, universalTimer, VSensor.WheelSpeed, StopNow.EStop); // determined whether to squeeze brake based on whether the user if doing anything (LR,UD) not = (128,128), what the trike speed is and if the ebrake has been triggered.
  steer.goToPos(Where.LR, universalTimer, VSensor.WheelSpeed, StopNow.EStop); //Steer motor go to where joystick is pointing on x-axis, based on wheter the quadstick has been triggered, and the speed of the trike, (and he positoin of the steering wheels, but that is had wired into the code.) 
  Go.applyThrottle(Where.UD, universalTimer, VSensor.WheelSpeed, StopNow.EStop); // determines how to appl throttle based on quadstick input, velocity, and whether EBrake has been triggered.
//  delay(100);
//  Serial.println(Where.UD); // debugging
//  Serial.println(Where.LR); // debugging

//if (checkmeter == 1000){
//  check3 = millis();
//  Serial.println(VSensor.WheelSpeed);
//  Serial.println(check4);
//  Serial.println(check1);
//  Serial.println(check2);
//  Serial.println(check3);
//  Serial.println();
//  check4 = millis();
//  checkmeter = 0;
//  } 
}


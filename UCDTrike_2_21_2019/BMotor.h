/*
  BMotor.h - Library for ALS Trike brake motor.
  Created by UCD ALS Trike Team, March 28, 2017.
  Source file is BMotor.cpp.
*/

#ifndef TRIKE_BRAKE //if TRIKE_BRAKE is not defined earlier, include the following (Prevent including library multiple times)
#define TRIKE_BRAKE

// define constants for braking motor

#define BRAKER_DIR 45
#define BRAKER_PWM 46
#define BRAKEL_DIR 43
#define BRAKEL_PWM 44

#define BRAKER_POT A3
#define BRAKEL_POT A4

#define BRAKE_SPINS_RIGHT 1
#define BRAKE_SPINS_LEFT 1

#define BRAKER_CURRENT_PIN A0
#define BRAKEL_CURRENT_PIN A1

#define NUM_BRAKE_CURRENT_SAMPLES 30
#define NUM_BRAKE_CURRENTS_FOR_AVERAGE 10

#define BRAKER_POT_CENTER 300
#define BRAKEL_POT_CENTER 620


// BMotor: this class controls the braking motor

class BMotor {
public:
  int dirPin; //directional Pin
  int speedPin; //speed pin
  int BPotVal; //value of potentiometer
  int BPotPin; //pin for the potentiometer
  int tightenPWM; //signal to send to motor in order to increase the braking power
  int loosenPWM; //opposite, currently unused
  int BrakePWM; //current braking power signal
  bool brakeOn; //indicator of whether brake is on
  unsigned long brakeEventClock; // keeps trake of when the brake is disengaged
  unsigned long noInputTimer;
  unsigned long noInputDelay;
  int maxEBrakePWM;
  int maxBrakePWM;
  int PotCenter;
  int i;
  int j;
  int currentData[NUM_BRAKE_CURRENT_SAMPLES];
  int totalCurrent;
  int currentPin;
  float currentsForAverage[NUM_BRAKE_CURRENTS_FOR_AVERAGE];
  float currentCurrent;
  unsigned long currentCounter;
  float currentCurrentsTotal;
  float currentAverage;
  int maxCurrent;
  

  
  BMotor(int dirPin, int speedPin, int BrakePotPin, bool brakeDirection, int brakeCurrentPin, int BrakePotCenter); 
  void setBrake(int setPos, int XPos, unsigned long timer, float velocity, bool EBrakeInput); //apply or release brake
  void brakeHarder(unsigned long timer);
};

#endif //if TRIKE_BRAKE is not defined earlier, include the code above

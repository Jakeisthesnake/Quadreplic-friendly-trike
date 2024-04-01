/* 
  SMotor.h - Library for ALS Trike steering motor.
  Created by UCD ALS Trike Team, March 8, 2017.
  Source file is SMotor.cpp.

  Information flow:
  1) Each loop, get:
  - Steering position via the potentiometer
  - Speed
  - Input from the quadstick
  2) Then calculate the max steering angle based on the speed.
  3) If the steering angle is greater than the max steering angle,
     calculate roation rate to move steering motor back towards center
     move steering motor towards center at calculated rater. 
  4) Otherwise
      check if input is a new input or if it had been help since last loop
      if new input
        caluculate rate of steering based on input, current steering position, and speed
        move steering at calculated rate
      if input had been held
       caluculate rate of steering based on time the input has been held, current steering position, and speed
        move steering at calculated rate
 */
// VERSION 1&2 VERSION 1&2 VERSION 1&2 VERSION 1&2 VERSION 1&2 VERSION 1&2 VERSION 1&2
/*
#define STEER_DIR 9 //define constant STEER_DIR with a value of 9
#define STEER_PWM 8 //define constant STEER_PWN with a value of 8

using namespace std;

//define SMotor class 
class SMotor {
private:
  int dirPin; 
  int	speedPin;
  unsigned long eventClock;
  int turnSpeed;
public:
  SMotor(int dPin, int sPin);
  void goToPos(int setPos, unsigned long timer);
};
*/
// VERSION 3 VERSION 3 VERSION 3 VERSION 3 VERSION 3 VERSION 3 VERSION 3


#define STEER_PWM_A 8 //define constant STEER_PWM_A with a value of 10 to drive one half bridge mosfet on motor driver
#define STEER_PWM_B 9 //define constant STEER_PWN_B with a value of 11 to drive other half bridge mosfet on motor driver
#define STEER_POT A2 //define constant STEER_POT with a value of A2
#define STEER_CURRENT_SENSOR A6 // Steering current sensor
#define NUM_STEER_CURRENT_SAMPLES 10 // Number of Current measurements taken.
#define NUM_STEER_CURRENTS_FOR_AVERAGE 10 // Number of Current measurements taken.
#define ENABLE_PIN 20// the pin that resets/enables the steering motor driver to turn on)


#define TOO_FAR_RIGHT 1
#define RIGHT_5 2
#define RIGHT_4 3
#define RIGHT_3 4
#define RIGHT_2 5
#define RIGHT_1 6
#define MIDDLE_STEERING 7
#define LEFT_1 8
#define LEFT_1 9
#define LEFT_1 10
#define LEFT_1 11
#define LEFT_1 12
#define LEFT_1 13
#define TOO_FAR_LEFT 14

using namespace std;


//define SMotor class 
class SMotor {
private:
  int sPin_a;
  int sPin_b;
  int speedPin;
  int groundPin;
  int speedPin_a;
  int speedPin_b;
  int EnablePin;
  int onPin;
  unsigned long eventClock;
  int eventDelay;
  int turnSpeed;
  int SPotVal;
  int SPotPin;
  int SCurrentPin;
  int steerCenter;
  int steerPos;
  bool turnedTooFar;
  float turnLimit;
  float maxTurnPower;
  int maxTurnSpeed;
  int ETurnSpeed;
  int zone;
  float maxCurrent;
  int currentCounter;
  int currentData[NUM_STEER_CURRENT_SAMPLES]; // for storing all the current values to average
  int i; // for counting the for loop to get an average current value
  int j;
  float totalCurrent; // stores the current averegare of the current sensor - get the pun?
  float currentAverage;  // stores the current averegare of the current sensor - get the pun?
  float currentCurrentsTotal;
  float currentCurrent;
  float currentsForAverage[NUM_STEER_CURRENTS_FOR_AVERAGE];
public:
  SMotor(int sPin_a, int sPin_b, int SPotVal, int SteerCurrentPin, int EnablePin);
  void goToPos(int setPos, unsigned long timer, float velocity, bool EBrakeInput);
  void turnHarder(unsigned long timer);
};

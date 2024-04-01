#include "RCcoord.h"
#define RC_EPIN 38
#define RC_ACTIVATE_PIN 32
#define RC_LR_PIN 35
#define RC_UD_PIN 39
using namespace std;

RCcoord::RCcoord(coord* c, EBrake* b){
  cd = c;
  eb = b;
  pinMode(RC_EPIN, INPUT);
  pinMode(RC_ACTIVATE_PIN, INPUT); // Set our input pins as such
  pinMode(RC_LR_PIN, INPUT);
  pinMode(RC_UD_PIN, INPUT);
}

int RCcoord::checkRC(){
  rcCheck = pulseIn(RC_ACTIVATE_PIN, HIGH);
//  Serial.println(rcCheck);
  if (rcCheck < 1450) return 1;
  if (rcCheck > 1450) return 0;
}

void RCcoord::checkRCEBrake(){
  rcEStop = pulseIn(RC_EPIN, HIGH);

  if ((rcEStop < 1300) || (rcEStop > 1600)){
    eb->EStop = 1;
  }
//  Serial.print("EStop =  ");
//  Serial.println(rcEStop);
}

void RCcoord::getCoord(){
  rcLR = pulseIn(RC_LR_PIN, HIGH);
  rcUD = pulseIn(RC_UD_PIN, HIGH);

  if ((rcLR < 1020) || (rcLR > 1880)){
    cd->LR = 128; // out of bounds
  }
  else if ((1300 < rcLR) && (rcLR < 1600)){
    cd->LR = 128; // dead zone
    }
  else {
    cd->LR = map(rcLR, 1020, 1880, 0, 255);
  }
  if ((rcUD < 1120) || (rcUD > 1940)){
    cd->UD = 128;
  }
  else if ((1450 < rcUD) && (rcUD < 1650)){
  cd->UD = 128; // dead zone
  }
  else {
    cd->UD = map(rcUD, 1120, 1940, 255, 0);
  }
//  Serial.println("Activate =  ");
//  Serial.println(rcCheck);
//  Serial.println("rcLR =  ");
//  Serial.println(map(rcLR, 1020, 1880, 0, 255));
//  Serial.println("rcUD =  ");
//  Serial.println(map(rcUD, 1120, 1950, 0, 255));
//  Serial.println("rcLR =  ");
//  Serial.println(rcLR);
}




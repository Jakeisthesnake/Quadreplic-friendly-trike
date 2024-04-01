//libraries
#include "coord.h"
#include "PS3USB.h"

using namespace std;

//set function coord as part of the coord class
coord::coord(USB* Usb){
  throttleVal = 0; //initially no speed
  if (Usb->Init() == -1) {
  Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
  LR = 128;
  UD = 128;
};

//declare function getPos under coord class. The function is expected to return no info.
void coord::getPos(USB Usb, PS3USB QS){
  Usb.Task(); //initiate a USB task 
  //Quadstick position corresponds to a PS3 controller's left joystick position (LeftHat)
  if (QS.PS3Connected){
    if (QS.getAnalogHat(LeftHatX) > 137 || QS.getAnalogHat(LeftHatX) < 117 || QS.getAnalogHat(LeftHatY) > 137 || QS.getAnalogHat(LeftHatY) < 117) {
      //print Quadstick x-axis position
     // Serial.print(F("\r\nX-Positon: "));
     // Serial.print(QS.getAnalogHat(LeftHatX));
      //print Quadstick y-axis position
     // Serial.print(F("\tY-Position: "));
      //Serial.print(QS.getAnalogHat(LeftHatY));
    }
    //pull analogue stick data from USB library
    int X_Val = map(QS.getAnalogHat(LeftHatX), 0, 255, 0, 255);
    int Y_Val = map(QS.getAnalogHat(LeftHatY), 255, 0, 255, 0);
    if (QS.getButtonClick(CROSS)) button = 2;

    if ((X_Val < 0) || (X_Val > 255)){ //ｃｈｅｃｋ　ｔｈｅ　ｉｎｐｕｔｓ　ａｒｅ　ｉｎ　ｒａｎｇe, otherwise don't turn trike
      LR = 128;
    }    
    else {
      LR = X_Val;
    }
    if ((Y_Val < 0) || (Y_Val > 255)){
      UD = 128;
    }
    else {
      UD = Y_Val;
    }
//    Serial.print("coord level UD   ");
//    Serial.println(UD);
//    Serial.print("coord level LR   ");
//    Serial.println(LR);
  }
  else{
    LR = 128;
    UD = 128;
    Serial.println("PS3 not connected");
  }
};

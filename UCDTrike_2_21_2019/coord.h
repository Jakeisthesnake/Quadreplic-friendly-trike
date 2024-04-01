/*
  coord.h - Library for ALS Trike Quadstick coordination.
  Created by UCD ALS Trike Team, April 4, 2017.
  Source file is coord.cpp.
*/
#ifndef COORD_H
#define COORD_H
#include "PS3USB.h"

using namespace std;

//define coord class
class coord{
public:
	int UD;
	int LR;
	int button;
	int throttleVal;
	void getPos(USB Usb, PS3USB QS);
	coord(USB* Usb);
	void scale();
};

#endif

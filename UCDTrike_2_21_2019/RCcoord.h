#include "coord.h"
#include "EBrake.h"

using namespace std;

class RCcoord{
public:
  coord* cd;
  EBrake* eb;
  RCcoord(coord* c, EBrake* b);
  void getCoord();
  void checkRCEBrake();
  int checkRC();
  int rcCheck;
  int rcEStop;
  int rcLR;
  int rcUD;
};


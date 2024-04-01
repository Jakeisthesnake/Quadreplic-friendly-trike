#define VELOCITY_PIN 17
#define GROUND_PIN 19

class Velocity{
public:
  int GPin;
  int VPin;
  int VState;
  int SwitchState;
  int rotationTicks;
  unsigned long VelocityTimer;
  float WheelSpeed; // how fast the wheel is rotating
  unsigned long lastVelocityTime; // last time a tick was recorded
  float deltaTicks; // change in distance since last tick
  float speedConstant; // wheel perimeter traveled per tick
  int lastTicksCount;
  float deltaTime;
  
  Velocity(int VelocityPin, int GroundPin);
  void getSpeed(unsigned long velocityTimer);
  
};

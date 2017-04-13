#include "RoviDC.cpp"
#include "config.cpp"
const int joystick = A0;

RoviDC *endEffector;
void setup() {
  endEffector = new RoviDC(8,9,10);
  pinMode(joystick, INPUT_PULLUP);
}

void loop() {

  endEffector->run( mapJoy(analogRead(joystick)) );
  
}

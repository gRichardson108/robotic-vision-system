#include "RoviDC.cpp"
const int j = A0;

RoviDC *endEffector;
void setup() {
  endEffector = new RoviDC(11,12,13);
  pinMode(j, INPUT_PULLUP);
}

void loop() {
  int x = analogRead(j)-512;
  if(x < -40 || x > 40)
  {
    endEffector->run( -2*x );
  }
  else {
    endEffector->run(0);
  }

}

#include <Arduino.h>

class RoviDC {
private:
  long pulseCount;//might experience overflow.
  unsigned long currentMillis;
  unsigned long previousStepMillis;
  unsigned long millisBetweenSteps;
  int pwmPin;
  int dirPinA;
  int dirPinB;

public:
  static const bool CLOCKWISE = true;

  RoviDC (int pwm_p, int dir_pin_a, int dir_pin_b)
  {
    pwmPin = pwm_p;
    dirPinA = dir_pin_a;
    dirPinB = dir_pin_b;
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPinA, OUTPUT);
    pinMode(dirPinB, OUTPUT);
  }

  void setDirection(bool dir) {
    digitalWrite(dirPinA, dir);
    digitalWrite(dirPinB, !dir);
  }

  void run(short velocity)
  {

    if (velocity > 0)
    {
      if(velocity>255) {
        velocity = 255;
      }
      // analogWrite(pwmPin, (byte)velocity);
      setDirection(CLOCKWISE);
    }
    else if(velocity < 0)
    {
      if(velocity < -255) {
        velocity = -255;
      }
      velocity *= -1;
      setDirection(!CLOCKWISE);
    }

    analogWrite(pwmPin, velocity);
  }


};

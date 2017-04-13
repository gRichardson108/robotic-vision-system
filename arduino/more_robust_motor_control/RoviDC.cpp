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
  static const int ANTI_OVERFLOW_OFFSET = 1000;
  static const bool CLOCKWISE = true;

  RoviDC (int pwm_p, int dir_pin_a, int dir_pin_b)
  {
    pulseCount = 0;
    pwmPin = pwm_p;
    dirPinA = dir_pin_a;
    dirPinB = dir_pin_b;
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPinA, OUTPUT);
    pinMode(dirPinB, OUTPUT);
    currentMillis = 0;
    millisBetweenSteps = 1000; //default 1 step per second.
  }
  void sync(unsigned long currTime)
  {
    currentMillis = currTime;
  }

  void resetPulseCount() {
    pulseCount = 0;
  }

  long getPulseCount() {
    return pulseCount;
  }

  void setDirection(bool dir) {
    digitalWrite(dirPinA,dir);
    digitalWrite(dirPinB,dir);
  }

  void setVelocity(short vel)
  {

    if (stepsPerSecond > 0)
    {
      digitalWrite(directionPin,CLOCKWISE);
      millisBetweenSteps = 1000 / stepsPerSecond;
    }
    else if(stepsPerSecond < 0)
    {
      digitalWrite(directionPin, !CLOCKWISE);
      millisBetweenSteps = (-1000) / stepsPerSecond;
    }

  }

  void step()
  {
    if (currentMillis - previousStepMillis >= millisBetweenSteps) {
      previousStepMillis += millisBetweenSteps;
      digitalWrite(stepPin, HIGH);
      digitalWrite(stepPin, LOW);
    }
  }
  //returns true iff we are at the step goal.
  bool stepTo(long stepGoal) {
    if (stepCount < stepGoal) {
      digitalWrite(directionPin, CLOCKWISE);
      step();
      return false;
    }
    else if(stepCount > stepGoal)
    {
      digitalWrite(directionPin, !CLOCKWISE);
      step();
      return false;
    }
    else {
      return true;
    }
  }


};

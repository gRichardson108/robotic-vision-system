#include <Arduino.h>
#define CLOCKWISE true

class RoviStepper {
private:
  long stepCount;//might experience overflow.
  unsigned long currentMillis;
  unsigned long previousStepMillis;
  unsigned long millisBetweenSteps;
  int directionPin;
  int stepPin;
public:
  static const int ANTI_OVERFLOW_OFFSET = 1000;

  RoviStepper (int step_p, int dir_p)
  {
    stepCount = 0;
    stepPin = step_p;
    directionPin = dir_p;
    pinMode(dir_p, OUTPUT);
    pinMode(step_p, OUTPUT);
    currentMillis = 0;
    millisBetweenSteps = 1000; //default 1 step per second.
  }
  void sync(unsigned long currTime)
  {
    currentMillis = currTime;
  }

  void resetStepCount() {
    stepCount = 0;
  }

  long getStepCount() {
    return stepCount;
  }
  //Mesured in steps per second. where positive is clockwise.
  //Maximum speed is 1000 steps per second.
  void setVelocity(long stepsPerSecond)
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

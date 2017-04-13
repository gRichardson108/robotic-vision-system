#include <Arduino.h>


class RoviStepper {
private:
  signed long netSteps;//might experience overflow.
  unsigned long currentMillis;
  unsigned long previousStepMillis;
  unsigned long millisBetweenSteps;
  int directionPin;
  int stepPin;
  bool currentDirection;
public:
  static const int ANTI_OVERFLOW_OFFSET = 1000;
  static const bool CLOCKWISE = true;
  RoviStepper (int step_p, int dir_p)
  {
    netSteps = 0;
    currentMillis = 0;
    millisBetweenSteps = 1000; //default 1 step per second.
    currentDirection = CLOCKWISE;

    stepPin = step_p;
    directionPin = dir_p;

    pinMode(dir_p, OUTPUT);
    pinMode(step_p, OUTPUT);
    digitalWrite(directionPin,currentDirection);
  }
  void sync(unsigned long currTime)
  {
    currentMillis = currTime;
  }

  void resetNetSteps() {
    netSteps = 0;
  }

  long getNetSteps() {
    return netSteps;
  }
  //Mesured in steps per second. where positive is clockwise.
  //Maximum speed is 1000 steps per second.
  void setVelocity(int stepsPerSecond)
  {
    if (stepsPerSecond > 0)
    {
      currentDirection = CLOCKWISE;
      millisBetweenSteps = 1000 / stepsPerSecond;
    }
    else if(stepsPerSecond < 0)
    {
      currentDirection = !CLOCKWISE;
      millisBetweenSteps = (-1000) / stepsPerSecond;
    }
    else return;

    digitalWrite(directionPin, currentDirection);
  }

  void step()
  {
    if (currentMillis - previousStepMillis >= millisBetweenSteps) {
      previousStepMillis += millisBetweenSteps;
      digitalWrite(stepPin, HIGH);
      digitalWrite(stepPin, LOW);
      netSteps += currentDirection ? 1 : -1;
    }
  }
  //returns true iff we are at the step goal.
  bool stepTo(long stepGoal) {
    if (netSteps < stepGoal) {
      currentDirection = CLOCKWISE;
    }
    else if(netSteps > stepGoal)
    {
      currentDirection = !CLOCKWISE;
    }
    else return true;

    digitalWrite(directionPin, currentDirection);
    step();
    return false;
  }


};

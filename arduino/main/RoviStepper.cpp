#include <Arduino.h>


class RoviStepper {
private:
  bool currentDirection;
  signed long netSteps;//might experience overflow.

  unsigned long currentMillis;
  unsigned long previousStepMillis;
  unsigned long millisBetweenSteps;

  unsigned short directionPin;
  unsigned short stepPin;
  unsigned short limitPinCW;
  unsigned short limitPinCCW;
public:
  static const int ANTI_OVERFLOW_OFFSET = 1000;
  static const bool CLOCKWISE = true;

  RoviStepper (const unsigned short step_p, const unsigned short dir_p,
    const unsigned short lim_p_cw, const unsigned short lim_p_ccw)
  {
    netSteps = 0;
    currentMillis = 0;
    millisBetweenSteps = 1000; //default 1 step per second.
    currentDirection = CLOCKWISE;

    stepPin = step_p;
    directionPin = dir_p;
    limitPinCW = lim_p_cw;
    limitPinCCW = lim_p_ccw;

    pinMode(stepPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(limitPinCW, INPUT);
    pinMode(limitPinCCW, INPUT);

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

  void setVelocity(long stepsPerSecond)
  {
   if (stepsPerSecond > 0)
   {
     currentDirection = CLOCKWISE;
     digitalWrite(directionPin,CLOCKWISE);
     millisBetweenSteps = 1000 / stepsPerSecond;
   }
   else if(stepsPerSecond < 0)
   {
     currentDirection = !CLOCKWISE;
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

  void run() {
    if (currentDirection == CLOCKWISE && digitalRead(limitPinCW)==LOW){
      return;
    }
    else if(currentDirection != CLOCKWISE && digitalRead(limitPinCCW)==LOW){
      return;
    }
    else step();
  }

  //returns true iff we are at the step goal.
  bool runTo(long stepGoal) {
    if (netSteps < stepGoal) {
      currentDirection = CLOCKWISE;
    }
    else if(netSteps > stepGoal)
    {
      currentDirection = !CLOCKWISE;
    }
    else return true;

    digitalWrite(directionPin, currentDirection);
    run();
    return false;
  }

  void stop() {
    digitalWrite(stepPin, false);
  }

};

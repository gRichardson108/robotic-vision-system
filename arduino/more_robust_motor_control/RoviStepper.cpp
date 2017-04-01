#include <Arduino.h>
#define CLOCKWISE true

class RoviStepper {
private:
  long steps;
  const int stepPin;
  const int dirPin;
  bool running;
  unsigned long previousMillis;
  unsigned long currentMillis;
public:
  RoviStepper (int step_p, int dir_p)
  {
    running = false;
    steps = 0;
    stepPin = step_p;
    dirPin = dir_p;
    previousMillis=millis();
  }

  void sync(unsigned long currTime)
  {
    currentMillis = currTime;
  }

  bool run(bool direction, int interval) {
    if (currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      digitalWrite(stepPin,false)
      running = false;
    }
    else {
      running = true;
      digitalWrite(dirPin,direction);
      digitalWrite(stepPin, true);
      steps++;
    }
    return running;
  }

  void stop() {
    digitalWrite(stepPin,false);
    running = false;
  }

  void runTo(bool direction, long stepGoal, int interval) {
    if (steps<stepGoal) {
      digitalWrite(stepPin,false);
      running = false;
    }
    else {
      run(direction, interval);
      running = true;
    }
    return running;
  }

};

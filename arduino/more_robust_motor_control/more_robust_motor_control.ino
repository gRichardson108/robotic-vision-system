#include "RoviStepper.cpp"

#define BASE                0
#define SHOULDER            1
#define ELBOW               2
#define WRIST               3

#define E_STOP_PIN                18
#define E_STOP_ENABLE_CHAR        'E'
#define E_STOP_VETO_CHAR          'V'
#define E_STOP_INTERRUPT_MODE     FALLING


bool soft_e_stop = false;
char received_char;

unsigned long sharedTimer;

RoviStepper *motors[4];
int joyPins[4];
void setup() {
                          //Step, direction, limitCW, limitCCW
  motors[BASE]     = new RoviStepper(3,4, 23,24);
  motors[SHOULDER] = new RoviStepper(5,6, 25,26);
  motors[ELBOW]    = new RoviStepper(7,8, 27,28);
  motors[WRIST]    = new RoviStepper(9,10,29,30);

  joyPins[BASE]     = A0;
  joyPins[SHOULDER] = A1;
  joyPins[ELBOW]    = A2;
  joyPins[WRIST]    = A3;

  for(int i = BASE; i <= WRIST; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  Serial.begin(9600);
/* Delete this line to test hardware emergency_stop button.

  pinMode(E_STOP_PIN, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(E_STOP_PIN), //converts the pin to an interrupt.
    emergency_stop, //interrupt routine callback.
    E_STOP_INTERRUPT_MODE
  );
/* */
}

void loop() {

  if (Serial.available() > 0) {
    received_char = Serial.read();
    Serial.print(received_char);
    if (received_char == E_STOP_ENABLE_CHAR){
      soft_e_stop = true;
    }
  }

  if(soft_e_stop)
  {
    emergency_stop();
  }

  sharedTimer = millis();

  manualJoyControlNoLimitSwitch();

  // manualJoystickControl();
}
void manualJoystickControl(){
  //For loop through all the motors, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    motors[i]->setVelocity( joystick(i) );
    motors[i]->sync(sharedTimer);
    motors[i]->run();
  }
}

int joystick(short whichJoystick) {
  #ifndef JOYCFG
  #define JOYCFG
  #define joystick_deadzone         42
  #define joystick_midpoint         512
  //True if joystick is  being moved.
  #define liveJoy(x) (x < joystick_midpoint-joystick_deadzone || x > joystick_midpoint+joystick_deadzone)
  // returns a the analog value of a live joystick to a range from -100 to +100, or to 0 if its dead.
  #define mapJoy(x) (liveJoy(x) ? (x-joystick_midpoint) : 0)
  #endif
  return mapJoy(
    analogRead( joyPins[whichJoystick] )
  );
}

void manualJoyControlNoLimitSwitch(){
  //For loop through all the motors, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    motors[i]->sync(sharedTimer);

    motors[i]->setVelocity( joystick(i) );
    motors[i]->step();
  }

}
void emergency_stop()
{
    noInterrupts();
    //force Stop motors NOW.
    for(short i = BASE; i <= WRIST; i++) {
      motors[i]->stop();
    }
    //Then, wait for veto.
    do
    {
      if(Serial.available() > 0)
      {
        received_char = Serial.read();
      }
    }while(received_char!=E_STOP_VETO_CHAR);
    soft_e_stop = false;

    interrupts();
}

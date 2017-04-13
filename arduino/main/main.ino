#include "RoviStepper.cpp"
#include "RoviDC.cpp"

#define BASE                0
#define SHOULDER            1
#define ELBOW               2
#define WRIST               3
#define HAND                4

#define E_STOP_PIN                18
#define E_STOP_ENABLE_CHAR        'E'
#define E_STOP_VETO_CHAR          'V'
#define E_STOP_INTERRUPT_MODE     FALLING


bool soft_e_stop = false;
char received_char;

unsigned long sharedTimer;

RoviStepper *arm[4];
RoviDC  *hand;
int joyPins[5];

void setup() {
  debug();
                          //Step, direction, limitCW, limitCCW
  arm[BASE]     = new RoviStepper(3,4, 22,23);
  arm[SHOULDER] = new RoviStepper(5,6, 24,25);
  arm[ELBOW]    = new RoviStepper(7,8, 26,27);
  arm[WRIST]    = new RoviStepper(9,10,28,29);
  hand  = new RoviDC(11,12,13);

  joyPins[BASE]     = A0;
  joyPins[SHOULDER] = A1;
  joyPins[ELBOW]    = A2;
  joyPins[WRIST]    = A3;
  joyPins[HAND]     = A4;

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
  //For loop through all the arm, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    arm[i]->setVelocity( joystick(i) );
    arm[i]->sync(sharedTimer);
    arm[i]->run();
  }
  hand->run( joystick[HAND] );

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
  //For loop through all the arm, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    arm[i]->sync(sharedTimer);

    arm[i]->setVelocity( joystick(i) );
    arm[i]->step();
  }
  hand->run( joystick[HAND] );

}
void emergency_stop()
{
    noInterrupts();
    //stop end effector
    hand->stop();
    //force Stop arm NOW.
    for(short i = BASE; i <= WRIST; i++) {
      arm[i]->stop();
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

void debug() {
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  digitalWrite(19,HIGH);
  digitalWrite(20,LOW);
}

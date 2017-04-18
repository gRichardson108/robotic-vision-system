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
#define E_STOP_INTERRUPT_MODE     LOW


bool soft_e_stop = false;
char received_char;

unsigned long sharedTimer;

RoviStepper *arm[4];
RoviDC  *hand;
int joyPins[5];

void setup() {
  debug();
  //Step, direction, limitCW, limitCCW
  arm[BASE]    = new RoviStepper(7,8, 26,27);
  arm[ELBOW]     = new RoviStepper(3,4, 22,23);
  arm[SHOULDER] = new RoviStepper(5,6, 24,25);
  arm[WRIST]    = new RoviStepper(9,10,28,29);
  hand  = new RoviDC(11,12,13);

  joyPins[BASE]     = A0;
  joyPins[SHOULDER] = A1;
  joyPins[ELBOW]    = A2;
  joyPins[WRIST]    = A3;
  joyPins[HAND]     = A4;

  for(int i = BASE; i <= WRIST; i++) {
    pinMode(joyPins[i], INPUT_PULLUP);
  }

  Serial.begin(9600);

  // Prepend this lind with a '/*' (no quotes) to use hardware emergency_stop button.
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

  // Serial.print("Hand");
  // Serial.println(joystick(HAND));
  // Serial.print("Base");
  // Serial.println(joystick(BASE));

  manualJoystickControl();
}
void manualJoystickControl(){
  hand->run( joystick(HAND)/8 );
  //For loop through all the arm, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    int vel =  joystick(i);
    //if(millis() % 1000 == 0) //Serial.println(vel);
    arm[i]->setVelocity( vel );
    arm[i]->sync(sharedTimer);
    arm[i]->run();
  }

}

int joystick(int whichJoystick) {
  int x;
  /*x = analogRead(joyPins[whichJoystick]);
  if(x < 350) {
    return 500;
  }else if (x > 650) return -500;
  else return 0;
  */
  static const int joystick_deadzone    =   42;
  static const int joystick_midpoint     =    512;
  //True if joystick is  being moved.
  x = analogRead(joyPins[whichJoystick])-joystick_midpoint;
  if(x < -joystick_deadzone || x > joystick_deadzone)
  {
    return -x;
  }
  else {
    return 0;
  }
}

void manualJoyControlNoLimitSwitch(){
  hand->run( joystick[HAND] );
  //For loop through all the arm, and move them if need be
  for(short i = BASE; i <= WRIST; i++)
  {
    arm[i]->sync(sharedTimer);

    arm[i]->setVelocity( joystick(i) );
    arm[i]->step();
  }

}
void emergency_stop()
{
    //noInterrupts();
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

//    interrupts();
}

void debug() {
  pinMode(19, OUTPUT);
  pinMode(20, OUTPUT);
  digitalWrite(19,HIGH);
  digitalWrite(20,LOW);
}
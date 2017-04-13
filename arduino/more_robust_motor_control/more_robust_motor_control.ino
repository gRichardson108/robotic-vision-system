#include "RoviStepper.cpp"
#include "config.cpp" //Defines pins and other constants.

int joyVals[4];
bool soft_e_stop = false;
char received_char;

unsigned long sharedTimer;

RoviStepper *motors[4];
void setup() {
                          //Step, direction, limitCW, limitCCW
  motors[base_index]     = new RoviStepper(3,4, 23,24);
  motors[shoulder_index] = new RoviStepper(5,6, 25,26);
  motors[elbow_index]    = new RoviStepper(7,8, 27,28);
  motors[wrist_index]    = new RoviStepper(9,10,29,30);

  pinMode(base_joy_sw_pin,     INPUT_PULLUP);
  pinMode(shoulder_joy_sw_pin, INPUT_PULLUP);
  pinMode(elbow_joy_sw_pin, INPUT_PULLUP);
  pinMode(wrist_joy_sw_pin, INPUT_PULLUP);

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
  for(short i = base_index; i <= wrist_index; i++)
  {
    motors[i]->setVelocity( joystick(i) );
    motors[i]->sync(sharedTimer);
    motors[i]->run();
  }
}

int joystick(short whichJoystick) {
  return mapJoy(
    analogRead( joyPins[whichJoystick] )
  );
}

void manualJoyControlNoLimitSwitch(){
  //For loop through all the motors, and move them if need be
  for(int i = base_index; i <= wrist_index; i++)
  {
    motors[i]->sync(sharedTimer);

    joyVals[i] = mapJoy(analogRead(joyPins[i]));

    motors[i]->setVelocity(joyVals[i]);
    motors[i]->step();
  }

}
void emergency_stop()
{
    noInterrupts();
    //force Stop motors NOW.
    for(int i = base_index; i <= wrist_index; i++) {
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

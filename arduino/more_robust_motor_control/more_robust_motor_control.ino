#include <MultiStepper.h>
#include <AccelStepper.h>

//Shoulder
#define shoulder_step_pin 3
#define shoulder_dir_pin 2
#define shoulder_lim_cw_pin 23
#define shoulder_lim_ccw_pin 22
#define shoulder_joy_x_pin A3
#define shoulder_joy_sw_pin 11

//Base
#define base_step_pin 9
#define base_dir_pin 8
#define base_lim_cw_pin 31
#define base_lim_ccw_pin 30
#define base_joy_x_pin A0
#define base_joy_sw_pin 12


#define joystick_threshold 500
bool emergency_stop = false;
char received_char;

#define s1 1500
#define s2 500
#define s3 250
int step_speed = s1; //higher means slower

AccelStepper mBase(AccelStepper::DRIVER, base_step_pin, base_dir_pin);

void setup() {
  mBase.setMaxSpeed(2000.0);
  mBase.setAcceleration(300.0);
  
  pinMode(base_lim_cw_pin, INPUT);
  pinMode(base_lim_ccw_pin, INPUT);
  
  pinMode(base_joy_sw_pin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() { 
 if (Serial.available() > 0) {
    emergency_stop = true;
    received_char = Serial.read();
    Serial.print(received_char);
    if (received_char == '0'){
      emergency_stop = false;
    }
  }

  
  mBase.stop();
 // mBase.setCurrentPosition(0);
  
  if (!digitalRead(base_joy_sw_pin)) {  //  If Joystick switch is clicked
    delay(500);  // delay for deboucing
    switch (step_speed) {  // check current value of step_speed and change it
      case s1:
        step_speed = s2; // fast speed
        break;
      case s2:
        step_speed = s3; // slow speed
        break;
      case s3:
        step_speed = s1; // medium speed
        break;
    }
  }

  
  if (digitalRead(base_lim_cw_pin)==HIGH && !emergency_stop && analogRead(base_joy_x_pin) > 540) {  //  If joystick is moved Left 712
    //Go clockwise
    mBase.setSpeed(step_speed);
    mBase.runSpeed();
  }

  if (digitalRead(base_lim_ccw_pin)==HIGH && !emergency_stop && analogRead(base_joy_x_pin) < 490) {  //  If joystick is moved Left 712
     mBase.setSpeed(-step_speed);
    mBase.runSpeed();
  }
  
  
}
/*
void manualJoyControl(int joystick, int stepper, int velocity, int limit)
{
  if( !emergency_stop && !limit && joystick > joystick_threshold)
  {
    stepperMove(stepper, velocity);
  }
}
*/


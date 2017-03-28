#include <MultiStepper.h>
#include <AccelStepper.h>

//Shoulder
#define shoulder_index 1
#define shoulder_step_pin 3
#define shoulder_dir_pin 2
#define shoulder_lim_cw_pin 23
#define shoulder_lim_ccw_pin 22
#define shoulder_joy_x_pin A3
#define shoulder_joy_sw_pin 11


//Base
#define base_index 0
#define base_step_pin 9
#define base_dir_pin 8
#define base_lim_cw_pin 31
#define base_lim_ccw_pin 30
#define base_joy_x_pin A0
#define base_joy_sw_pin 12


#define E_STOP_INTERRUPT 0
#define E_STOP_VETO_CHAR 'V'
#define E_STOP_INTERRUPT_MODE RISING

#define joystick_deadzone 40
bool soft_e_stop = false;
char received_char;


//True if joystick is  being moved.
#define liveJoy(x) (x < 512-joystick_deadzone || x > 512+joystick_deadzone)
// returns a the analog value of a live joystick to a range from -100 to +100, or to 0 if its dead.
#define mapJoy(x) (liveJoy(x) ? (200*x-102300)/1023 : 0)

#define s1 1500
#define s2 500
#define s3 250
int step_speed = s1; //higher means slower

void speedShift();

mBase(AccelStepper::DRIVER, base_step_pin, base_dir_pin);
mShoulder(AccelStepper::DRIVER, shoulder_step_pin, shoulder_dir_pin);

MultiStepper allSteppers;

void setup() {

  mBase.setMaxSpeed(2000.0);
  mShoulder.setMaxSpeed(2000.0);

  allSteppers.addStepper(mBase);
  allSteppers.addStepper(mShoulder);

  pinMode(base_lim_cw_pin, INPUT);
  pinMode(base_lim_ccw_pin, INPUT);

  pinMode(base_joy_sw_pin, INPUT_PULLUP);

  Serial.begin(9600);

  attachInterrupt(E_STOP_INTERRUPT, emergency_stop, E_STOP_INTERRUPT_MODE);
}

void loop() {
 if (Serial.available() > 0) {
    soft_e_stop = true;
    received_char = Serial.read();
    Serial.print(received_char);
    if (received_char == '0'){
      soft_e_stop = false;
    }
  }

  if(soft_e_stop)
  {
    emergency_stop();
  }

  manualJoyControl();
}


void manualJoyControl(){
  //Get an array of desired  FROM JOYSTICk;
  int joyVal = mapJoy(analogRead(base_joy_x_pin));

  //handle limit switches
  //If the limit switch is not pressed and we are are going forward
  if(digitalRead(base_lim_cw_pin)!=LOW && joyVal(base_joy_x_pin)>0)
  {
    //Move if necessary
    mBase.setSpeed(step_speed);
    mBase.runSpeed(step_speed);
  }
  else if(digitalRead(base_lim_ccw_pin)!=LOW && joyVal(base_joy_x_pin)>0)
  {
    mBase.setSpeed(-step_speed);
    mBase.runSpeed(step_speed);
  }
  else
  {
    mBase.stop();
  }
  //Shoulder
  int joyVal = mapJoy(analogRead(shoulder_joy_x_pin));

  //handle limit switches
  //If the limit switch is not pressed and we are are going forward
  if(digitalRead(shoulder_lim_cw_pin)!=LOW && joyVal(shoulder_joy_x_pin)>0)
  {
    //Move if necessary
    mShoulder.setSpeed(step_speed);
    mShoulder.runSpeed(step_speed);
  }
  else if(digitalRead(shoulder_lim_ccw_pin)!=LOW && joyVal(shoulder_joy_x_pin)>0)
  {
    mShoulder.setSpeed(-step_speed);
    mShoulder.runSpeed(step_speed);
  }
  else
  {
    mShoulder.stop();
  }

}

void emergency_stop()
{
    //Stop motors NOW.
    //Then, wait for veto.
    do
    {
      if(Serial.available() > 0)
      {
        received_char = Serial.read();
      }
    }while(received_char!=E_STOP_VETO_CHAR);
}

void speedShift()
{
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
}

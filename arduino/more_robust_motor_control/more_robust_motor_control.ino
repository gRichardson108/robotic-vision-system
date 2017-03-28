#include <MultiStepper.h>
#include <AccelStepper.h>

//Shoulder
#define shoulder_index 1
#define shoulder_step_pin 7
#define shoulder_dir_pin 4
#define shoulder_lim_cw_pin 23
#define shoulder_lim_ccw_pin 22
#define shoulder_joy_x_pin A0
#define shoulder_joy_sw_pin 11
#define shoulder_max_speed 3000.0
//Base
#define base_index 0
#define base_step_pin 9
#define base_dir_pin 8
#define base_lim_cw_pin 31
#define base_lim_ccw_pin 30
#define base_joy_x_pin A3
#define base_joy_sw_pin 12
#define base_max_speed 2000.0

#define E_STOP_INTERRUPT 0
#define E_STOP_VETO_CHAR 'V'
#define E_STOP_INTERRUPT_MODE RISING

#define joystick_deadzone 42
bool soft_e_stop = false;
char received_char;


//True if joystick is  being moved.
#define liveJoy(x) (x < 512-joystick_deadzone || x > 512+joystick_deadzone)
// returns a the analog value of a live joystick to a range from -100 to +100, or to 0 if its dead.
#define mapJoy(x) (liveJoy(x) ? (x-512) : 0)

#define s1 1500
#define s2 500
#define s3 250
int step_speed = s1; //higher means slower
int joyVals[5];
const int joyPins[] = {
  base_joy_x_pin,
  shoulder_joy_x_pin,
  0,
  0,
  0
};
const int limitPinsCW[] = {
  base_lim_cw_pin,
  shoulder_lim_cw_pin,
  0,
  0,
  0
};
const int limitPinsCCW[] = {
  base_lim_ccw_pin,
  shoulder_lim_ccw_pin,
  0,
  0,
  0
};

const float speedFactors[] = {
  base_max_speed/512,
  shoulder_max_speed/512,
  0,
  0,
  0
};
AccelStepper mBase(AccelStepper::DRIVER, base_step_pin, base_dir_pin);
AccelStepper mShoulder(AccelStepper::DRIVER, shoulder_step_pin, shoulder_dir_pin);

AccelStepper *motors[5];

MultiStepper allSteppers;

void setup() {
  motors[0] = &mBase;
  motors[1] = &mShoulder;

  mBase.setMaxSpeed(base_max_speed);
  mBase.setAcceleration(0.0);
  mShoulder.setMaxSpeed(shoulder_max_speed);
  mShoulder.setAcceleration(0.0);

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
    received_char = Serial.read();
    Serial.print(received_char);
    if (received_char == '1'){
      soft_e_stop = true;
    }
  }

  if(soft_e_stop)
  {
    emergency_stop();
  }

  manualJoyControl();
}


void manualJoyControl(){
  for(int i = 0; i < 2; i++)
  {

    //Get  desired  FROM JOYSTICk;
    joyVals[i] = mapJoy(analogRead(joyPins[i]));

    //handle limit switches
    //If the limit switch is not pressed and we are are going forward
    if(digitalRead(limitPinsCW[i])!=LOW && joyVals[i]>0)
    {
      //Move if necessary
      motors[i]->setSpeed(speedFactors[i]*joyVals[i]);
      motors[i]->runSpeed();
    }
    else if(digitalRead(limitPinsCCW[i])!=LOW && joyVals[i]<0)
    {
      motors[i]->setSpeed(speedFactors[i]*joyVals[i]);
      motors[i]->runSpeed();
    }
    else
    {
      motors[i]->stop();
    }
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

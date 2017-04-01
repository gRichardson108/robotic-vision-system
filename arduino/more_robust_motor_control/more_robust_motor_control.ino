#include <MultiStepper.h>
#include <AccelStepper.h>
#include "config.cpp"


int joyVals[4];
bool soft_e_stop = false;
char received_char;
AccelStepper mBase(AccelStepper::DRIVER, base_step_pin, base_dir_pin);
AccelStepper mShoulder(AccelStepper::DRIVER, shoulder_step_pin, shoulder_dir_pin);
AccelStepper mElbow(AccelStepper::DRIVER,elbow_step_pin,elbow_dir_pin);
AccelStepper mWrist(AccelStepper::DRIVER,wrist_step_pin,wrist_dir_pin);

AccelStepper *motors[4];

//MultiStepper allSteppers;

void setup() {
  motors[base_index]     = &mBase;
  motors[shoulder_index] = &mShoulder;
  motors[elbow_index]    = &mElbow;
  motors[wrist_index]    = &mWrist;
  for(int i = 0; i<4; i++) {
    motors[i]->setMaxSpeed(maxSpeeds[i]);
    motors[i]->setAcceleration(speedFactors[i]);
  }
  //
  // mBase.setMaxSpeed(base_max_speed);
  // mBase.setAcceleration(0.0);
  // mShoulder.setMaxSpeed(shoulder_max_speed);
  // mShoulder.setAcceleration(0.0);

  //allSteppers.addStepper(mBase);
  //allSteppers.addStepper(mShoulder);

  pinMode(base_lim_cw_pin, INPUT);
  pinMode(base_lim_ccw_pin, INPUT);
  pinMode(shoulder_lim_cw_pin, INPUT);
  pinMode(shoulder_lim_ccw_pin, INPUT);
  pinMode(elbow_lim_cw_pin, INPUT);
  pinMode(elbow_lim_ccw_pin, INPUT);
  pinMode(wrist_lim_cw_pin, INPUT);
  pinMode(wrist_lim_ccw_pin, INPUT);

  pinMode(base_joy_sw_pin, INPUT_PULLUP);
  pinMode(shoulder_joy_sw_pin, INPUT_PULLUP);
  pinMode(elbow_joy_sw_pin, INPUT_PULLUP);
  pinMode(wrist_joy_sw_pin, INPUT_PULLUP);

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
  for(int i = 0; i < 4; i++)
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
    for(int i=0; i<4;i++) {
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
}

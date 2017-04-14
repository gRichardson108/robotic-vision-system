#include "RoviStepper.cpp"
#include "config.cpp" //Defines pins and other constants.

int joyVals[4];
bool soft_e_stop = false;
char received_char;

unsigned long sharedTimer;

RoviStepper *motors[4];
void setup() {
  motors[base_index]     = new RoviStepper(base_step_pin,     base_dir_pin);
  motors[shoulder_index] = new RoviStepper(shoulder_step_pin, shoulder_dir_pin);
  motors[elbow_index]    = new RoviStepper(elbow_step_pin,    elbow_dir_pin);
  motors[wrist_index]    = new RoviStepper(wrist_step_pin,    wrist_dir_pin);

  pinMode(base_lim_cw_pin,  INPUT);
  pinMode(base_lim_ccw_pin, INPUT);
  pinMode(shoulder_lim_cw_pin,  INPUT);
  pinMode(shoulder_lim_ccw_pin, INPUT);
  pinMode(elbow_lim_cw_pin,  INPUT);
  pinMode(elbow_lim_ccw_pin, INPUT);
  pinMode(wrist_lim_cw_pin,  INPUT);
  pinMode(wrist_lim_ccw_pin, INPUT);

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

  manualJoyControl();

}


void manualJoyControl(){
  //For loop through all the motors, and move them if need be
  for(int i = base_index; i <= wrist_index; i++)
  {
    motors[i]->sync(sharedTimer);
    //Get  desired  FROM JOYSTICk;
    joyVals[i] = mapJoy(analogRead(joyPins[i]));
    //If the limi switch is not pressed and the motor is moving  clockwise
    if(/*digitalRead(limitPinsCW[i])!=LOW &&*/ joyVals[i]>0)
    {
      motors[i]->setVelocity(100);
      motors[i]->step();
    }
    //if the limit switch is not pressed and the motor is moving counter clockwise
    else if(/*digitalRead(limitPinsCCW[i])!=LOW &&*/ joyVals[i]<0)
    {
      motors[i]->setVelocity(-100);
      motors[i]->step();
    }

  }

}
void emergency_stop()
{
    //force Stop motors NOW.
    digitalWrite(base_step_pin, LOW);
    digitalWrite(shoulder_step_pin, LOW);
    digitalWrite(elbow_step_pin, LOW);
    digitalWrite(wrist_step_pin, LOW);

    //Then, wait for veto.
    do
    {
      if(Serial.available() > 0)
      {
        received_char = Serial.read();
      }
    }while(received_char!=E_STOP_VETO_CHAR);
    soft_e_stop = false;
}

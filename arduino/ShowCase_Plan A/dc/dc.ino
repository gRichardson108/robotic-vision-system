#include "RoviDC.cpp"
#include "config.cpp"
#include <Stepper.h>
const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution
const int joystick = A4;
Stepper small_stepper(stepsPerRevolution, 8,9); 

Stepper small_stepper2(stepsPerRevolution, 2,3);

Stepper small_stepper3(stepsPerRevolution, 4,5);

Stepper small_stepper4(stepsPerRevolution, 6,7);
RoviDC *endEffector;
char received_char;
bool soft_e_stop = false;
#define E_STOP_ENABLE_CHAR        'E'
#define E_STOP_VETO_CHAR          'V'

void setup() {
    // set the speed of the motors

  small_stepper.setSpeed(1000);    // set first stepper speed

  small_stepper2.setSpeed(1000);   // set second stepper speed

  small_stepper3.setSpeed(1000);   // set third stepper speed

  small_stepper4.setSpeed(1000);   // set third stepper speed

  endEffector = new RoviDC(10,11,12);
  pinMode(joystick, INPUT_PULLUP);

  Serial.begin(9600);
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
  
  int sensorReading = analogRead(A0); // read value from joystick X-axis

 

  if (sensorReading < 490) { small_stepper.step(1); }   // step left

  if (sensorReading > 540) { small_stepper.step(-1); }  // step right

  

  int sensorReading2 = analogRead(A1); // read value from joystick Y-axis



  if (sensorReading2 < 490) { small_stepper2.step(1); } // step forward

  if (sensorReading2 > 540) { small_stepper2.step(-1); } // step backward

  
  int sensorReading3 = analogRead(A2); // read value from joystick X-axis

  if (sensorReading3 < 490) { small_stepper3.step(1); } // step forward

  if (sensorReading3 > 540) { small_stepper3.step(-1); } // step backward

  int sensorReading4 = analogRead(A3); // read value from joystick X-axis

  if (sensorReading4 < 490) { small_stepper4.step(-1); } // step forward

  if (sensorReading4 > 540) { small_stepper4.step(1); } // step backward

  endEffector->run( mapJoy(analogRead(joystick)) );
  
}

void emergency_stop()
{
    do
    {
      if(Serial.available() > 0)
      {
        received_char = Serial.read();
      }
    }while(received_char!=E_STOP_VETO_CHAR);
    soft_e_stop = false;

}

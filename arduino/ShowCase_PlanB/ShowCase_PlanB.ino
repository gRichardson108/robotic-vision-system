// http://www.bajdi.com

// 3 stepper motors controlled by a joystick

#include <Stepper.h>

 

const int stepsPerRevolution = 512;  // change this to fit the number of steps per revolution

// for your motor

// initialize the stepper library for both steppers:

Stepper small_stepper(stepsPerRevolution, 8,9); 

Stepper small_stepper2(stepsPerRevolution, 2,3);

Stepper small_stepper3(stepsPerRevolution, 4,5);

Stepper small_stepper4(stepsPerRevolution, 6,7);
 

void setup() {

 

  // set the speed of the motors

  small_stepper.setSpeed(1000);    // set first stepper speed

  small_stepper2.setSpeed(1000);   // set second stepper speed

  small_stepper3.setSpeed(1000);   // set third stepper speed

  small_stepper4.setSpeed(1000);   // set third stepper speed

}

 

 

void loop() {

  

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

 }


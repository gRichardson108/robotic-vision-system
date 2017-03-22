#include <MultiStepper.h>
#include <AccelStepper.h>

#define step_pin 3  // Pin 9 connected to Steps pin on EasyDriver
#define dir_pin 2  // Pin 8 connected to Direction pin

#define Joy_01 A3    // Pin A3 connected to joystick x axis
#define Joy_sw01 11  // Pin 11 connected to joystick switch


#define Limit01 23  // Pin 23 connected to Limit switch out
#define Limit02 22  // Pin 32 connected to Limit switch out

int step_speed = 1;  // Speed of Stepper motor (higher = slower)
int emergency_stop = 0; // when not 0, all motors must be stopped
char received_char;

AccelStepper mShoulder;

void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);

  pinMode(Limit01, INPUT);
  pinMode(Limit02, INPUT);

  pinMode(Joy_sw01, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    emergency_stop = 1;
    received_char = Serial.read();
    Serial.print(received_char);
    if (received_char == '0'){
      emergency_stop = 0;
    }
  }
  if (!digitalRead(Joy_sw01)) {  //  If Joystick switch is clicked
    delay(500);  // delay for deboucing
    switch (step_speed) {  // check current value of step_speed and change it
      case 10:
        step_speed = 1; // fast speed
        break;
      case 3:
        step_speed = 10; // slow speed
        break;
      case 1:
        step_speed = 3; // medium speed
        break;
    }
  }

  if (analogRead(Joy_01) > 540) {  //  If joystick is moved Left 712
    if (!digitalRead(Limit01) || emergency_stop != 0) {}  // check if limit switch is activated

    else {  //  if limit switch is not activated, move motor clockwise

      digitalWrite(dir_pin, LOW);  // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delay(step_speed);
      digitalWrite(step_pin, LOW);
      delay(step_speed);
    }
  }

  if (analogRead(Joy_01) < 490) {  // If joystick is moved right 312

    if (!digitalRead(Limit02) || emergency_stop != 0) {}  // check if limit switch is activated

    else {  //  if limit switch is not activated, move motor counter clockwise

      digitalWrite(dir_pin, HIGH);  // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(step_pin, HIGH);
      delay(step_speed);
      digitalWrite(step_pin, LOW);
      delay(step_speed);
    }
  }
}

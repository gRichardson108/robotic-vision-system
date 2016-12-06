#include <Servo.h>
#include <math.h>

Servo servo;

const float pi = 3.14159265359;


float ObjX, ObjY;    // object coordinates
float SerX, SerY, junk;
float MotorX, MotorY; // motor coordinates
float deltaX, deltaY; // coordinate difference
float angleRad, angleDeg;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
}

void motorTurn(int ObjX,int ObjY) {

  deltaX = ObjX - MotorX;
  deltaY = ObjY - MotorY;
  
  if (deltaX > 0 ) {
    angleRad = atan(deltaY/deltaX);   // get angle from servo to object
  }
  else {
    angleRad = pi + atan(deltaY/deltaX);
  }
  
  angleDeg = angleRad * (180/pi); //convert the angle from radians (angleRad) to degrees (angleDeg).

  if (angleDeg > 180) {
    angleDeg = -(360-angleDeg); // keep the angles between -180 to 180 degrees
  }
  
  Serial.print("Coordinate: ");
  Serial.print(ObjX);
  Serial.print(",");
  Serial.println(ObjY);
  Serial.print("Angle: ");
  Serial.println(angleDeg);
  Serial.println(" degrees");
  
  //if (angleDeg > 5 && angleDeg < 175) {
    servo.write(angleDeg);
    delay(1000);
// }
}

void loop() {
  // define motor position
  MotorX = 2.5; 
  MotorY = 1;
  
  motorTurn(1,4);
  delay(1000);
  motorTurn(2,4);
  delay(1000);
  motorTurn(3,4);
  delay(1000);
  motorTurn(4,4);
  delay(1000);
  motorTurn(5,4);
  delay(1000);
  
  
  // manual coordinates
  Serial.print("\nCustom Coordinate X\n");
  while (Serial.available() == 0) ;  // Wait here until input buffer has a character
  {
      //Side 1
    SerX = Serial.parseFloat();        // new command in 1.0 forward
    Serial.print("X = "); 
    Serial.println(SerX, DEC);
    while (Serial.available() > 0)  // .parseFloat() can leave non-numeric characters
    { junk = Serial.read() ; }      // clear the keyboard buffer
  }
  Serial.print("\nCustom Coordinate Y\n");
  while (Serial.available() == 0) ;
  {
      //Side 2
    SerY = Serial.parseFloat();
    Serial.print("Y = "); 
    Serial.println(SerY, DEC);
    while (Serial.available() > 0)
    { junk = Serial.read() ; }
  }
  
  motorTurn(SerX, SerY);
  delay(1000);
}

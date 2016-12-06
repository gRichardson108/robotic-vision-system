#include <Servo.h>
#include <math.h>

Servo *twist;
Servo *arm;
const float pi = 3.14159265359;

float MotorX, MotorY; // motor coordinates
void serialTurn(Servo*);
void motorTurn(Servo*,float,float);
bool parseMessage(float output[3]);// retrieve <X,Y,Theta> coordinates
void moveAll(float x, float y, float theta);

void setup() {
  Serial.begin(9600);
  twist = new Servo();
  twist->attach(9);

  arm = new Servo();
  arm->attach(10);
  
  // define motor position
  MotorX = 2.5; 
  MotorY = 1;

  arm->write(0);
  twist->write(0);
}

void loop() {
  float message[3];
  if(parseMessage(message)) {
    moveAll(message[0],message[1],message[2]);
  }
}

void moveAll(float x, float y, float theta) {
  arm->write(theta);
  motorTurn(twist,x,y);
}

void serialTurn(Servo *servo)
{
  float SerX, SerY, junk;
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
  
  motorTurn(servo, SerX, SerY);
  
}

void motorTurn(Servo* servo, float ObjX,float ObjY) {

  float deltaX = ObjX - MotorX;
  float deltaY = ObjY - MotorY;
  float angleDeg, angleRad;
  if (deltaX > 0 ) {
    angleRad = atan(deltaY/deltaX);   // get angle from twist to object
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
    servo->write(angleDeg);
    delay(400);
// }
}

bool parseMessage(float output[3]){
  char c = 0;
  if(!Serial.available()){
    return false;   
  }else{
    c = Serial.read();
  }
  if(c != '<') {
    return false;
  }
  for(int i=0; i<3; i++) {
    output[i] = Serial.parseFloat();
  }
  return true;
}


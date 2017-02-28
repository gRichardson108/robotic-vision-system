#include <Servo.h>
#include <math.h>

#define SERVO_MIN 0
#define SERVO_CALIBRATE (-2)
#define SERVO_MAX 173

//#define clamp(x,mn,mx) ((x<mn)?(mn):(x>mx)?(mx):(x))

Servo *twist;
Servo *arm;

//float MotorX, MotorY; // motor coordinates
void serialTurn(Servo*);
//void pointOnPlain(Servo*, float, float);
bool parseMessage(float output[2]);// retrieve <horizontal,vertical> angles
void moveAll(float angle, float theta);
float message[2];

void setup() {
	Serial.begin(9600);
 
	twist = new Servo();
	twist->attach(9);

	arm = new Servo();
	arm->attach(10);

/*
	// define motor position
	MotorX = 0;
	MotorY = 0;
*/

	message[0] = 0;
	message[1] = 120;

  twist->write(90);
	arm->write(90);
}

void loop() {
	if (!parseMessage(message)) {
		moveAll(message[0], message[1]);
		int output = twist->read();
		Serial.println(message[0]);
		Serial.println(message[1]);
		Serial.println(output);
		Serial.println();
		delay(10);
	}
}

void moveAll(float arm_angle, float theta) {
  if (arm_angle > SERVO_MAX)
    arm_angle = SERVO_MAX;
  else if (arm_angle < SERVO_MIN) 
    arm_angle = SERVO_MIN;

	twist->write(arm_angle);
	arm->write(theta);
}


void serialTurn(Servo *servo)
{
	float SerX, SerY, junk;
	// manual coordinates
	Serial.print("\nCustom Coordinate X\n");
	while (Serial.available() == 0);  // Wait here until input buffer has a character
	{
		//Side 1
		SerX = Serial.parseFloat();        // new command in 1.0 forward
		Serial.print("X = ");
		Serial.println(SerX, DEC);
		while (Serial.available() > 0)  // .parseFloat() can leave non-numeric characters
		{
			junk = Serial.read();
		}      // clear the keyboard buffer
	}
	Serial.print("\nCustom Coordinate Y\n");
	while (Serial.available() == 0);
	{
		//Side 2
		SerY = Serial.parseFloat();
		Serial.print("Y = ");
		Serial.println(SerY, DEC);
		while (Serial.available() > 0)
		{
			junk = Serial.read();
		}
	}

//	pointOnPlain(servo, SerX, SerY);
}

/*
void pointOnPlain(Servo* servo, float ObjX, float ObjY) {
	bool negative = false;
	float deltaX = ObjX - MotorX;
	float deltaY = ObjY - MotorY;
	float angleDeg, angleRad;
	if (deltaX > 0) {
		angleRad = atan(deltaY / deltaX);   // get angle from twist to object
	}
	else {
		angleRad = PI + atan(deltaY / deltaX);
	}

	angleDeg = angleRad * (180 / PI); //convert the angle from radians (angleRad) to degrees (angleDeg).

	if (angleDeg > 180) {
		angleDeg = -(360 - angleDeg); // keep the angles between -180 to 180 degrees
	}

	//Keep angle within servo range of motion
	negative = angleDeg < 0;
	angleDeg = fmod(abs(angleDeg), 360) + SERVO_CALIBRATE;

	servo->write(clamp(angleDeg, SERVO_MIN, SERVO_MAX));
	delay(400);
}
*/

bool parseMessage(float output[2]) {
	char c = 0;
	if (Serial.available() <= 0) {
		return false;
	}
	else {
		c = Serial.read();
	
		if (c != '<') {
			return false;
		}
		for (int i = 0; i < 1; i++) {
			output[i] = Serial.parseFloat();
		}
		return true;
	}
}



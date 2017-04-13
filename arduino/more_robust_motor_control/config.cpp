#include <Arduino.h>
//Base
#define base_index                0
#define base_joy_x_pin            A0
#define base_joy_sw_pin           10

//Shoulder
#define shoulder_index            1
#define shoulder_joy_x_pin        A1
#define shoulder_joy_sw_pin       11

//elbow
#define elbow_index                2
#define elbow_joy_x_pin            A2
#define elbow_joy_sw_pin           12

//wrist
#define wrist_index                3
#define wrist_joy_x_pin            A3
#define wrist_joy_sw_pin           13

//emergency stop pin must be one of the following: 2, 3, 18, 19, 20, 21
#define E_STOP_PIN                 18
#define E_STOP_ENABLE_CHAR        'E'
#define E_STOP_VETO_CHAR          'V'
#define E_STOP_INTERRUPT_MODE     FALLING

#define joystick_deadzone         42
#define joystick_midpoint         512

//True if joystick is  being moved.
#define liveJoy(x) (x < joystick_midpoint-joystick_deadzone || x > joystick_midpoint+joystick_deadzone)
// returns a the analog value of a live joystick to a range from -100 to +100, or to 0 if its dead.
#define mapJoy(x) (liveJoy(x) ? (x-joystick_midpoint) : 0)

const int joyPins[] = {
  base_joy_x_pin,
  shoulder_joy_x_pin,
  elbow_joy_x_pin,
  wrist_joy_x_pin
};

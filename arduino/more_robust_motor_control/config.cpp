#include <Arduino.h>
//Shoulder
#define shoulder_index            1
#define shoulder_step_pin         3
#define shoulder_dir_pin          2
#define shoulder_lim_cw_pin       23
#define shoulder_lim_ccw_pin      22
#define shoulder_joy_x_pin        A1
#define shoulder_joy_sw_pin       11
#define shoulder_max_speed        2000.0
//Base
#define base_index                0
#define base_step_pin             5
#define base_dir_pin              4
#define base_lim_cw_pin           27
#define base_lim_ccw_pin          29
#define base_joy_x_pin            A0
#define base_joy_sw_pin           10
#define base_max_speed            2000.0

//elbow
#define elbow_index                2
#define elbow_step_pin             7
#define elbow_dir_pin              6
#define elbow_lim_cw_pin           33
#define elbow_lim_ccw_pin          32
#define elbow_joy_x_pin            A2
#define elbow_joy_sw_pin           12
#define elbow_max_speed            2000.0

//wrist
#define wrist_index                3
#define wrist_step_pin             9
#define wrist_dir_pin              8
#define wrist_lim_cw_pin           39
#define wrist_lim_ccw_pin          38
#define wrist_joy_x_pin            A3
#define wrist_joy_sw_pin           13
#define wrist_max_speed            2000.0



#define E_STOP_INTERRUPT          0
#define E_STOP_VETO_CHAR          'V'
#define E_STOP_INTERRUPT_MODE     RISING

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
const int limitPinsCW[] = {
  base_lim_cw_pin,
  shoulder_lim_cw_pin,
  elbow_lim_cw_pin,
  wrist_lim_cw_pin
};
const int limitPinsCCW[] = {
  base_lim_ccw_pin,
  shoulder_lim_ccw_pin,
  elbow_lim_ccw_pin,
  wrist_lim_ccw_pin
};

const float maxSpeeds[] = {
  base_max_speed,
  shoulder_max_speed,
  elbow_max_speed,
  wrist_max_speed
};

const float speedFactors[] = {
  base_max_speed/joystick_midpoint,
  shoulder_max_speed/joystick_midpoint,
  elbow_max_speed/joystick_midpoint,
  wrist_max_speed/joystick_midpoint
};

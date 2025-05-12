#ifndef joystick_included
#define joystick_included

#include <Arduino.h>

// parameters for reading the joystick:
constexpr int range = 12;            // output range of X or Y movement
constexpr int threshold = range / 4; // resting threshold
constexpr int center = range / 2;    // resting position value

int readAxis(int thisAxis);

#endif
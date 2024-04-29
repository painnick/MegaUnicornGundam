#pragma once

// These are all GPIO pins on the ESP32
// Recommended pins include 2,4,12-19,21-23,25-27,32-33
// for the ESP32-S2 the GPIO pins are 1-21,26,33-42

#define PIN_MP3_TX 33 // dfplayer(FIXED)
#define PIN_MP3_RX 32 // dfplayer(FIXED)

#define SG90msForServo0Degree 500
#define SG90msForServo180Degree 2500

#define USE_PCA9685_SERVO_EXPANDER
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 16
#define ENABLE_EASE_ELASTIC
#define DEBUG

#include <ServoEasing.hpp>

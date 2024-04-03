#include <Arduino.h>

#define USE_PCA9685_SERVO_EXPANDER
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 16
#define ENABLE_EASE_CUBIC
#define DEBUG

#define SG90msForServo0Degree 500
#define SG90msForServo180Degree 2500

#include <ServoEasing.hpp>

#include "esp_log.h"

#define MAIN_TAG "main"

#define SERVO1_PIN  0
#define AnkleLeft_PIN  2
#define AnkleRight_PIN  3

void getAndAttach16ServosToPCA9685Expander(uint8_t aPCA9685I2CAddress) {
    ServoEasing *tServoEasingObjectPtr;

    Serial.print(F("Get ServoEasing objects and attach servos to PCA9685 expander at address=0x"));
    Serial.println(aPCA9685I2CAddress, HEX);
    for (uint_fast8_t i = 0; i < PCA9685_MAX_CHANNELS; ++i) {
        tServoEasingObjectPtr = new ServoEasing(aPCA9685I2CAddress);
        if (tServoEasingObjectPtr->attach(i, 90, SG90msForServo0Degree, SG90msForServo180Degree) == INVALID_SERVO) {
            ESP_LOGE(MAIN_TAG, "Not Attached! #%d", i);
        }
    }
}

void setup() {
    ESP_LOGI(MAIN_TAG, "InitializeAndCheckI2CConnection...");

    Wire.begin();
    checkI2CConnection(PCA9685_DEFAULT_ADDRESS, &Serial);
    getAndAttach16ServosToPCA9685Expander(PCA9685_DEFAULT_ADDRESS);

    ESP_LOGI(MAIN_TAG, "Attached!");
    delay(2000);
}

void loop() {
    setSpeedForAllServos(30);

    for (uint_fast8_t i = 0; i <= ServoEasing::sServoArrayMaxIndex; ++i) {
        ServoEasing::ServoEasingArray[i]->startEaseTo(180);
    }
    delay(6000);

    for (uint_fast8_t i = 0; i <= ServoEasing::sServoArrayMaxIndex; ++i) {
        ServoEasing::ServoEasingArray[i]->startEaseTo(90);
    }
    delay(6000);

    for (uint_fast8_t i = 0; i <= ServoEasing::sServoArrayMaxIndex; ++i) {
        ServoEasing::ServoEasingArray[i]->startEaseTo(0);
    }
    delay(6000);

    for (uint_fast8_t i = 0; i <= ServoEasing::sServoArrayMaxIndex; ++i) {
        ServoEasing::ServoEasingArray[i]->startEaseTo(90);
    }
    delay(6000);
}


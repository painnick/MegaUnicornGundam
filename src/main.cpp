#include <Arduino.h>

#define USE_PCA9685_SERVO_EXPANDER
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 1
#define ENABLE_EASE_CUBIC
#define DEBUG

#define SG90msForServo0Degree 500
#define SG90msForServo180Degree 2500

#include <ServoEasing.hpp>

#include "esp_log.h"

#define MAIN_TAG "main"

ServoEasing Servo1(PCA9685_DEFAULT_ADDRESS); // If you use more than one PCA9685 you probably must modify MAX_EASING_SERVOS
#define SERVO1_PIN  0

void setup()
{
    ESP_LOGI(MAIN_TAG, "InitializeAndCheckI2CConnection...");

    delay(2000);

    auto connectecd = Servo1.InitializeAndCheckI2CConnection(&Serial);

    if (Servo1.attach(SERVO1_PIN, 90, SG90msForServo0Degree, SG90msForServo180Degree) == INVALID_SERVO) {
        Serial.println(F("Error attaching servo"));
        while (true) {
            delay(1000);
        }
    }
    ESP_LOGI(MAIN_TAG, "Attached!");
    delay(2000);
}

void loop()
{
    ESP_LOGI(MAIN_TAG, "Go to 180");
    Servo1.startEaseTo(180, 30, START_UPDATE_BY_INTERRUPT);
    delay(6 * 1000);

    ESP_LOGI(MAIN_TAG, "Go to 90");
    Servo1.startEaseTo(90, 30, START_UPDATE_BY_INTERRUPT);
    delay(6 * 1000);

    ESP_LOGI(MAIN_TAG, "Go to 0");
    Servo1.startEaseTo(0, 30, START_UPDATE_BY_INTERRUPT);
    delay(6 * 1000);

    ESP_LOGI(MAIN_TAG, "Go to 90");
    Servo1.startEaseTo(90, 30, START_UPDATE_BY_INTERRUPT);
    delay(6 * 1000);
}

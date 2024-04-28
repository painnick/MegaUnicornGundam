#include <Arduino.h>
#include "esp_log.h"

#include "common.h"
#include "controllers/Mp3Controller.h"

#define USE_PCA9685_SERVO_EXPANDER
#define DISABLE_COMPLEX_FUNCTIONS
#define MAX_EASING_SERVOS 16
#define ENABLE_EASE_CUBIC
#define DEBUG

#define SG90msForServo0Degree 500
#define SG90msForServo180Degree 2500

#include <ServoEasing.hpp>

#include <Adafruit_NeoPixel.h>

#define MAIN_TAG "main"

#define INIT_DEGREE_COMMON 90
#define INIT_DEGREE_KNEE 45
#define INIT_DEGREE_ANKLE 30

// Ankle 20(Up tiptoe)~90(Down tiptoe)
#define AnkleLeft_PIN  2
#define AnkleRight_PIN  3

// Knee 45(Stand)~90(Fold)
#define KneeLeft_PIN  4
#define KneeRight_PIN  5

#define HipJointLeft_PIN 6
#define HipJointRight_PIN 7


#define PIN_STRIP_STAGE 18
#define STRIP_STAGE_SIZE 4
Adafruit_NeoPixel stripStage = Adafruit_NeoPixel(STRIP_STAGE_SIZE, PIN_STRIP_STAGE, NEO_GRB + NEO_KHZ800);

void getAndAttach16ServosToPCA9685Expander(uint8_t aPCA9685I2CAddress) {
    ServoEasing *tServoEasingObjectPtr;

    Serial.print(F("Get ServoEasing objects and attach servos to PCA9685 expander at address=0x"));
    Serial.println(aPCA9685I2CAddress, HEX);
    for (int i = 0; i < PCA9685_MAX_CHANNELS; ++i) {
        tServoEasingObjectPtr = new ServoEasing(aPCA9685I2CAddress);
        int initDegree = INIT_DEGREE_COMMON;
        switch (i) {
            case KneeLeft_PIN:
            case KneeRight_PIN:
                initDegree = INIT_DEGREE_KNEE;
                break;
            case AnkleLeft_PIN:
            case AnkleRight_PIN:
                initDegree = INIT_DEGREE_ANKLE;
                break;
            default:
                initDegree = INIT_DEGREE_COMMON;
        }

        if (tServoEasingObjectPtr->attach(i, initDegree, SG90msForServo0Degree, SG90msForServo180Degree) == INVALID_SERVO) {
            ESP_LOGE(MAIN_TAG, "Not Attached! #%d", i);
        }
    }
}

void setup() {
    stripStage.setBrightness(255);
    for (int i = 0; i < STRIP_STAGE_SIZE; i++)
        stripStage.setPixelColor(i, 255, 63, 0);
    stripStage.show();

    ESP_LOGI(MAIN_TAG, "InitializeAndCheckI2CConnection...");

    Wire.begin();
    checkI2CConnection(PCA9685_DEFAULT_ADDRESS, &Serial);
    getAndAttach16ServosToPCA9685Expander(PCA9685_DEFAULT_ADDRESS);

    ESP_LOGI(MAIN_TAG, "Attached!");
    delay(2000);
}

void loop() {
    ESP_LOGI(MAIN_TAG, "Walk Forward...");
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->mSpeed = 30;
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->startEaseTo(90 - 30);

    ServoEasing::ServoEasingArray[KneeLeft_PIN]->mSpeed = 60;
    ServoEasing::ServoEasingArray[KneeLeft_PIN]->startEaseTo(90);

    ServoEasing::ServoEasingArray[AnkleLeft_PIN]->mSpeed = 60;
    ServoEasing::ServoEasingArray[AnkleLeft_PIN]->startEaseTo(20);

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Walk Backward...");
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->mSpeed = 30;
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->startEaseTo(90 + 10);

    delay(300);

    ServoEasing::ServoEasingArray[KneeLeft_PIN]->mSpeed = 45;
    ServoEasing::ServoEasingArray[KneeLeft_PIN]->startEaseTo(INIT_DEGREE_KNEE);

    ServoEasing::ServoEasingArray[AnkleLeft_PIN]->mSpeed = 45;
    ServoEasing::ServoEasingArray[AnkleLeft_PIN]->startEaseTo(INIT_DEGREE_ANKLE);

    delay(1800 - 500 + 800);

    ESP_LOGI(MAIN_TAG, "Stand Up!");
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->mSpeed = 30;
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->startEaseTo(90 - 15);

    ServoEasing::ServoEasingArray[KneeLeft_PIN]->mSpeed = 45;
    ServoEasing::ServoEasingArray[KneeLeft_PIN]->startEaseTo(60);

    delay(1000);

    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->mSpeed = 30;
    ServoEasing::ServoEasingArray[HipJointLeft_PIN]->startEaseTo(90);

    ServoEasing::ServoEasingArray[KneeLeft_PIN]->mSpeed = 45;
    ServoEasing::ServoEasingArray[KneeLeft_PIN]->startEaseTo(INIT_DEGREE_KNEE);

    delay(1000 * 10);

}


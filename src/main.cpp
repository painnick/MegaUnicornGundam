#include <Arduino.h>

#include "common.h"
#include "controllers/Mp3Controller.h"
#include "controllers/HipJointController.h"
#include "controllers/KneeController.h"
#include "controllers/AnkleController.h"
#include "controllers/BodyController.h"

#include <Wire.h>

#include <Adafruit_NeoPixel.h>

#define MAIN_TAG "main"

#define AnkleLeft_PIN  2
#define AnkleRight_PIN  3

#define KneeLeft_PIN  4
#define KneeRight_PIN  5

#define HipJointLeft_PIN 6
#define HipJointRight_PIN 7

#define Body_PIN 8

#define PIN_STRIP_STAGE 18
#define STRIP_STAGE_SIZE 4
Adafruit_NeoPixel stripStage = Adafruit_NeoPixel(STRIP_STAGE_SIZE, PIN_STRIP_STAGE, NEO_GRB + NEO_KHZ800);


HipJointController HipJointLeft(PCA9685_DEFAULT_ADDRESS, "HipJoint-Left");
HipJointController HipJointRight(PCA9685_DEFAULT_ADDRESS, "HipJoint-Right");
KneeController KneeLeft(PCA9685_DEFAULT_ADDRESS, "Knee-Left");
KneeController KneeRight(PCA9685_DEFAULT_ADDRESS, "Knee-Right");
AnkleController AnkleLeft(PCA9685_DEFAULT_ADDRESS, "Ankle-Left");
AnkleController AnkleRight(PCA9685_DEFAULT_ADDRESS, "Ankle-Right");
BodyController Body(PCA9685_DEFAULT_ADDRESS, "Body");

void getAndAttach16ServosToPCA9685Expander(uint8_t aPCA9685I2CAddress) {
    HipJointLeft.attach(HipJointLeft_PIN);
    HipJointRight.attach(HipJointRight_PIN);

    KneeLeft.attach(KneeLeft_PIN);
    KneeRight.attach(KneeRight_PIN);

    AnkleLeft.attach(AnkleLeft_PIN);
    AnkleRight.attach(AnkleRight_PIN);

    Body.attach(Body_PIN);
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
    ESP_LOGI(MAIN_TAG, "Left Step...");
    Body.setSpeed(15);
    Body.backward(15);

    HipJointLeft.setSpeed(30);
    HipJointLeft.forward(30);

    KneeLeft.setSpeed(60);
    KneeLeft.backward(45);

    AnkleLeft.setSpeed(60);
    AnkleLeft.forward(20);

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Stand up...");

    Body.setSpeed(15);
    Body.standUp();

    HipJointLeft.setSpeed(30);
    HipJointLeft.standUp();

    delay(300);

    KneeLeft.setSpeed(50);
    KneeLeft.standUp();

    AnkleLeft.setSpeed(45);
    AnkleLeft.standUp();

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Right Step...");
    Body.setSpeed(15);
    Body.forward(15);

    HipJointRight.setSpeed(30);
    HipJointRight.forward(30);

    KneeRight.setSpeed(60);
    KneeRight.backward(45);

    AnkleRight.setSpeed(60);
    AnkleRight.forward(20);

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Stand up...");

    Body.setSpeed(15);
    Body.standUp();

    HipJointRight.setSpeed(30);
    HipJointRight.standUp();

    delay(300);

    KneeRight.setSpeed(50);
    KneeRight.standUp();

    AnkleRight.setSpeed(45);
    AnkleRight.standUp();

    delay(1000 * 10);

}


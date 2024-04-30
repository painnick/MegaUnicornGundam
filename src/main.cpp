#include <Arduino.h>

#include "common.h"
#include "controllers/Mp3Controller.h"
#include "controllers/HipJointLeftController.h"
#include "controllers/HipJointRightController.h"
#include "controllers/KneeController.h"
#include "controllers/AnkleController.h"
#include "controllers/BodyController.h"
#include "controllers/NeckController.h"
#include "controllers/Neck2Controller.h"
#include "controllers/ShoulderLeftController.h"
#include "controllers/ShoulderRightController.h"

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
#define Neck_PIN 9

#define ArmLeft_PIN 10
#define ArmRight_PIN 11

#define ShoulderLeft_PIN 12
#define ShoulderRight_PIN 13

#define Neck2_PIN 14

#define PIN_STRIP_STAGE 18
#define STRIP_STAGE_SIZE 4
Adafruit_NeoPixel stripStage = Adafruit_NeoPixel(STRIP_STAGE_SIZE, PIN_STRIP_STAGE, NEO_GRB + NEO_KHZ800);


HipJointLeftController HipJointLeft(PCA9685_DEFAULT_ADDRESS, "HipJoint-Left");
HipJointRightController HipJointRight(PCA9685_DEFAULT_ADDRESS, "HipJoint-Right");
KneeController KneeLeft(PCA9685_DEFAULT_ADDRESS, "Knee-Left");
KneeController KneeRight(PCA9685_DEFAULT_ADDRESS, "Knee-Right");
AnkleController AnkleLeft(PCA9685_DEFAULT_ADDRESS, "Ankle-Left");
AnkleController AnkleRight(PCA9685_DEFAULT_ADDRESS, "Ankle-Right");
BodyController Body(PCA9685_DEFAULT_ADDRESS, "Body");
NeckController Neck(PCA9685_DEFAULT_ADDRESS, "Neck");

DefaultServoController ArmLeft(PCA9685_DEFAULT_ADDRESS, "Arm-Left");
DefaultServoController ArmRight(PCA9685_DEFAULT_ADDRESS, "Arm-Right");

ShoulderLeftController ShoulderLeft(PCA9685_DEFAULT_ADDRESS, "Shoulder-Left");
ShoulderRightController ShoulderRight(PCA9685_DEFAULT_ADDRESS, "Shoulder-Right");

Neck2Controller Neck2(PCA9685_DEFAULT_ADDRESS, "Neck2");

void getAndAttach16ServosToPCA9685Expander(uint8_t aPCA9685I2CAddress) {
    HipJointLeft.attach(HipJointLeft_PIN);
    HipJointRight.attach(HipJointRight_PIN);

    KneeLeft.attach(KneeLeft_PIN);
    KneeRight.attach(KneeRight_PIN);

    AnkleLeft.attach(AnkleLeft_PIN);
    AnkleRight.attach(AnkleRight_PIN);

    Body.attach(Body_PIN);
    Neck.attach(Neck_PIN);

    ShoulderLeft.attach(ShoulderLeft_PIN);
    ShoulderRight.attach(ShoulderRight_PIN);

    ArmLeft.attach(ArmLeft_PIN);
    ArmRight.attach(ArmRight_PIN);

    Neck2.attach(Neck2_PIN);
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

    KneeLeft.setEasingType(EASE_ELASTIC_OUT);
    KneeLeft.setSpeed(2000);
    KneeLeft.startBackwardTo(45);

    delay(1000);

    Body.setSpeed(15);
    Body.startBackwardTo(15);

    Neck.setSpeed(15);
    Neck.startBackwardTo(15);

    HipJointLeft.setSpeed(20);
    HipJointLeft.startForwardTo(30);

    HipJointRight.setSpeed(10);
    HipJointRight.startBackwardTo(10);

    ShoulderLeft.setSpeed(20);
    ShoulderLeft.startBackwardTo(20);

    ShoulderRight.setSpeed(20);
    ShoulderRight.startForwardTo(20);

    AnkleLeft.setSpeed(60);
    AnkleLeft.startForwardTo(20);

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Stand up...");

    Body.setSpeed(15);
    Body.startStandUp();

    Neck.setSpeed(15);
    Neck.startStandUp();

    HipJointLeft.setSpeed(30);
    HipJointLeft.startStandUp();

    HipJointRight.setSpeed(10);
    HipJointRight.startStandUp();

    ShoulderLeft.setSpeed(30);
    ShoulderLeft.startStandUp();

    ShoulderRight.setSpeed(30);
    ShoulderRight.startStandUp();

    delay(300);

    KneeLeft.setEasingType(EASE_LINEAR);
    KneeLeft.setSpeed(50);
    KneeLeft.startStandUp();

    AnkleLeft.setSpeed(45);
    AnkleLeft.startStandUp();

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Right Step...");
    Body.setSpeed(15);
    Body.startForwardTo(15);

    Neck.setSpeed(15);
    Neck.startForwardTo(15);

    HipJointRight.setSpeed(20);
    HipJointRight.startForwardTo(30);

    HipJointLeft.setSpeed(10);
    HipJointLeft.startBackwardTo(10);

    ShoulderLeft.setSpeed(20);
    ShoulderLeft.startBackwardTo(20);

    ShoulderLeft.setSpeed(20);
    ShoulderLeft.startForwardTo(20);

    KneeRight.setSpeed(60);
    KneeRight.startBackwardTo(45);

    AnkleRight.setSpeed(60);
    AnkleRight.startForwardTo(20);

    delay(1800);

    ESP_LOGI(MAIN_TAG, "Stand up...");

    Body.setSpeed(15);
    Body.startStandUp();

    Neck.setSpeed(15);
    Neck.startStandUp();

    HipJointRight.setSpeed(30);
    HipJointRight.startStandUp();

    HipJointLeft.setSpeed(10);
    HipJointLeft.startStandUp();

    ShoulderLeft.setSpeed(30);
    ShoulderLeft.startStandUp();

    ShoulderRight.setSpeed(30);
    ShoulderRight.startStandUp();

    delay(300);

    KneeRight.setSpeed(50);
    KneeRight.startStandUp();

    AnkleRight.setSpeed(45);
    AnkleRight.startStandUp();

    delay(1000 * 2);

    Neck.setSpeed(30);
    Neck.forward(20);

    delay(500);

    Neck.standUp();

    delay(500);

    Neck.backward(20);

    delay(500);

    Neck.standUp();

    delay(1000);

    Neck2.setSpeed(30);
    Neck2.forward(30);

    delay(500);

    Neck2.standUp();

    delay(500);

    Neck2.backward(60);

    delay(500);

    Neck2.startStandUp();

    delay(1000 * 10);
}


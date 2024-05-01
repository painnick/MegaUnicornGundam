//
// Created by painnick on 2024-04-30.
//
#pragma once

#include "controllers/HipJointLeftController.h"
#include "controllers/HipJointRightController.h"
#include "controllers/KneeController.h"
#include "controllers/AnkleController.h"
#include "controllers/BodyController.h"
#include "controllers/NeckController.h"
#include "controllers/Neck2Controller.h"
#include "controllers/ShoulderLeftController.h"
#include "controllers/ShoulderRightController.h"

#define AnkleLeft_PIN  2
#define AnkleRight_PIN  3

#define KneeLeft_PIN  4
#define KneeRight_PIN  5

#define HipJointLeft_PIN 6
#define HipJointRight_PIN 7

#define Body_PIN 8
#define Neck_PIN 9

#define ShoulderLeft_PIN 12
#define ShoulderRight_PIN 13

#define Neck2_PIN 14

#define MOVEMENT_TAG "move"

class MovementManager {
public:
    MovementManager() {
        HipJointLeft = new HipJointLeftController(PCA9685_DEFAULT_ADDRESS, "HipJoint-Left");
        HipJointRight = new HipJointRightController(PCA9685_DEFAULT_ADDRESS, "HipJoint-Right");
        KneeLeft = new KneeController(PCA9685_DEFAULT_ADDRESS, "Knee-Left");
        KneeRight = new KneeController(PCA9685_DEFAULT_ADDRESS, "Knee-Right");
        AnkleLeft = new AnkleController(PCA9685_DEFAULT_ADDRESS, "Ankle-Left");
        AnkleRight = new AnkleController(PCA9685_DEFAULT_ADDRESS, "Ankle-Right");
        Body = new BodyController(PCA9685_DEFAULT_ADDRESS, "Body");
        Neck = new NeckController(PCA9685_DEFAULT_ADDRESS, "Neck");

        ShoulderLeft = new ShoulderLeftController(PCA9685_DEFAULT_ADDRESS, "Shoulder-Left");
        ShoulderRight = new ShoulderRightController(PCA9685_DEFAULT_ADDRESS, "Shoulder-Right");

        Neck2 = new Neck2Controller(PCA9685_DEFAULT_ADDRESS, "Neck2");
    };

    void attach() {
        HipJointLeft->attach(HipJointLeft_PIN);
        HipJointRight->attach(HipJointRight_PIN);

        KneeLeft->attach(KneeLeft_PIN);
        KneeRight->attach(KneeRight_PIN);

        AnkleLeft->attach(AnkleLeft_PIN);
        AnkleRight->attach(AnkleRight_PIN);

        Body->attach(Body_PIN);
        Neck->attach(Neck_PIN);

        ShoulderLeft->attach(ShoulderLeft_PIN);
        ShoulderRight->attach(ShoulderRight_PIN);

        Neck2->attach(Neck2_PIN);
        ESP_LOGI(MOVEMENT_TAG, "Attached.");
    }

    ~MovementManager() = default;

    void initSpeed() {
        Body->setSpeed(15);
        Neck->setSpeed(20);
        ShoulderLeft->setSpeed(20);
        ShoulderRight->setSpeed(20);
        AnkleLeft->setSpeed(60);
        AnkleRight->setSpeed(60);
        Neck2->setSpeed(30);
    }

    void headXY() {
        Neck->left(20);
        delay(500);

        Neck->standUp();
        delay(500);

        Neck->right(20);
        delay(500);

        Neck->standUp();
        delay(500);
    }

    void headZ() {
        Neck2->forward(30);
        delay(500);

        Neck2->standUp();
        delay(500);

        Neck2->backward(60);
        delay(500);

        Neck2->standUp();
        delay(500);
    }

    void leftStep() {
        ESP_LOGI(MOVEMENT_TAG, "Left Step...");

        // 무릎을 먼저 굽힘
        KneeLeft->setSpeed(30);
        KneeLeft->startBackwardTo(30);

        // 몸통을 반대로 틀고, 고개는 정방향
        Body->startRightTo(15);
        Neck->startLeftTo(20);

        // --------------------
        // 왼쪽 다리 들기
        // --------------------
        HipJointLeft->setSpeed(20);
        HipJointLeft->startForwardTo(30);

        HipJointRight->setSpeed(10);
        HipJointRight->startBackwardTo(10);

        // 고관절과 반대 방향
        ShoulderLeft->startBackwardTo(20);
        ShoulderRight->startForwardTo(20);

        delay(1800);
    }

    void rightStep() {
        ESP_LOGI(MOVEMENT_TAG, "Right Step...");

        // 무릎을 먼저 굽힘
        KneeRight->setSpeed(30);
        KneeRight->startBackwardTo(30);

        // 몸통을 반대로 틀고, 고개는 정방향
        Body->startLeftTo(15);
        Neck->startRightTo(20);

        // --------------------
        // 오른쪽 다리 들기
        // --------------------
        HipJointLeft->setSpeed(20);
        HipJointLeft->startBackwardTo(30);

        HipJointRight->setSpeed(10);
        HipJointRight->startForwardTo(10);

        // 고관절과 반대 방향
        ShoulderLeft->startForwardTo(20);
        ShoulderRight->startBackwardTo(20);

        delay(1800);
    }

    void standUp() {
        ESP_LOGI(MOVEMENT_TAG, "StandUp...");

        Body->startStandUp();
        Neck->startStandUp();

        HipJointLeft->setSpeed(30);
        HipJointLeft->startStandUp();

        HipJointRight->setSpeed(10);
        HipJointRight->startStandUp();

        ShoulderLeft->startStandUp();
        ShoulderRight->startStandUp();

        // 무릎을 조금 늦게 폄
        delay(300);

        KneeLeft->setSpeed(50);
        KneeLeft->startStandUp();

        KneeRight->setSpeed(50);
        KneeRight->startStandUp();

        delay(1000);
    }

protected:
    HipJointLeftController *HipJointLeft;
    HipJointRightController *HipJointRight;
    KneeController *KneeLeft;
    KneeController *KneeRight;
    AnkleController *AnkleLeft;
    AnkleController *AnkleRight;
    BodyController *Body;
    NeckController *Neck;

    ShoulderLeftController *ShoulderLeft;
    ShoulderRightController *ShoulderRight;

    Neck2Controller *Neck2;
};

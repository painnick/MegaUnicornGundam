//
// Created by painnick on 2024-04-29.
//
// Left와 모터 회전 방향이 다름
//
#pragma once

#include "DefaultServoController.h"

class HipJointRightController : public DefaultServoController {
public:
    int initDegree() override { return 90; }

    int minDegree() override { return 90 - 10; }

    int maxDegree() override { return 90 + 30; }

    explicit HipJointRightController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}

    void startForwardTo(int targetDegree) override {
        int degree = initDegree() + targetDegree;
        startEaseTo(min(degree, maxDegree()));
    };

    void startBackwardTo(int targetDegree) override {
        int degree = initDegree() - targetDegree;
        startEaseTo(max(degree, minDegree()));
    };
};

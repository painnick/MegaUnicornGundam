//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class ShoulderLeftController : public DefaultServoController {
public:
    int initDegree() override { return 90; }

    int minDegree() override { return 0; }

    int maxDegree() override { return 180; }

    void startForwardTo(int targetDegree) override {
        int degree = initDegree() + targetDegree;
        startEaseTo(max(degree, minDegree()));
    };

    void startBackwardTo(int targetDegree) override {
        int degree = initDegree() - targetDegree;
        startEaseTo(min(degree, maxDegree()));
    };

    explicit ShoulderLeftController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}
};

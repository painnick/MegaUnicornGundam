//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class Neck2Controller : public DefaultServoController {
public:
    int initDegree() override { return 110; }

    int minDegree() override { return 45; }

    int maxDegree() override { return 135; }

    void forward(int targetDegree) override {
        int degree = initDegree() + targetDegree;
        easeTo(max(degree, minDegree()));
    };

    void backward(int targetDegree) override {
        int degree = initDegree() - targetDegree;
        easeTo(min(degree, maxDegree()));
    };

    explicit Neck2Controller(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}
};

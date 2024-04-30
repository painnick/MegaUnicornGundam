//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class XYServoController : public DefaultServoController {
public:

    void startLeftTo(int targetDegree) {
        int degree = initDegree() - targetDegree * (reverseDirection ? -1 : 1);
        startEaseTo(max(degree, minDegree()));
    };

    void startRightTo(int targetDegree) {
        int degree = initDegree() + targetDegree * (reverseDirection ? -1 : 1);
        startEaseTo(min(degree, maxDegree()));
    };

    void left(int targetDegree) {
        int degree = initDegree() - targetDegree * (reverseDirection ? -1 : 1);
        easeTo(max(degree, minDegree()));
    };

    void right(int targetDegree) {
        int degree = initDegree() + targetDegree * (reverseDirection ? -1 : 1);
        easeTo(min(degree, maxDegree()));
    };

    explicit XYServoController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {
    }
};

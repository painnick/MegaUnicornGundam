//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class HipJointController : public DefaultServoController {
public:
    int initDegree() override { return 90; }

    int minDegree() override { return 90 - 30; }

    int maxDegree() override { return 90 + 10; }

    explicit HipJointController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}
};

//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "XYServoController.h"

class BodyController : public XYServoController {
public:
    int initDegree() override { return 90; }

    int minDegree() override { return 30; }

    int maxDegree() override { return 120; }

    explicit BodyController(uint8_t aPCA9685I2CAddress, const String &nickName) : XYServoController(
            aPCA9685I2CAddress, nickName) {
    }
};

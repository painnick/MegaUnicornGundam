//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class AnkleController : public DefaultServoController {
public:
    int initDegree() override { return 30; }

    int minDegree() override { return 20; }

    int maxDegree() override { return 90; }

    explicit AnkleController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}
};

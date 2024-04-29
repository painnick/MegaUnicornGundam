//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "DefaultServoController.h"

class KneeController : public DefaultServoController {
public:
    int initDegree() override { return 45; }

    int minDegree() override { return 45; }

    int maxDegree() override { return 90; }

    explicit KneeController(uint8_t aPCA9685I2CAddress, const String &nickName) : DefaultServoController(
            aPCA9685I2CAddress, nickName) {}
};

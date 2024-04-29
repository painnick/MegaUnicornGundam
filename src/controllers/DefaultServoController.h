//
// Created by painnick on 2024-04-29.
//
#pragma once

#include "common.h"

#define DEFAULT_SERVO_TAG "DefaultServo"

class DefaultServoController {
public:
    virtual int initDegree() { return 90; }

    virtual int minDegree() { return 0; }

    virtual int maxDegree() { return 180; }

    virtual int msForServo0Degree() { return SG90msForServo0Degree; }

    virtual int msForServo180Degree() { return SG90msForServo180Degree; }

    explicit DefaultServoController(uint8_t aPCA9685I2CAddress, const String &nickName) {
        this->nickName = nickName;
        tServoEasingObjectPtr = new ServoEasing(aPCA9685I2CAddress);
    };

    virtual ~DefaultServoController() = default;

    virtual void attach(int pinNo) {
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) Attached [Pin #%2d] [Init %3d] [Min %3d] [Max %3d]",
                 &nickName, pinNo, initDegree(), msForServo0Degree(), msForServo180Degree());
        servoIndex = tServoEasingObjectPtr->attach(pinNo, initDegree(), msForServo0Degree(), msForServo180Degree());
    }

    virtual void setSpeed(uint_fast16_t speed) {
        ServoEasing::ServoEasingArray[servoIndex]->setSpeed(speed);
    };

    int startEaseTo(int targetDegree) const {
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) StartEaseTo %3d", &nickName, targetDegree);
        ServoEasing::ServoEasingArray[servoIndex]->startEaseTo(targetDegree);
        return ServoEasing::ServoEasingArray[servoIndex]->getEndMicrosecondsOrUnits();
    }

    void easeTo(int targetDegree) const {
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) EaseTo %3d", &nickName, targetDegree);
        ServoEasing::ServoEasingArray[servoIndex]->easeTo(targetDegree);
    }

    void startStandUp() {
        startEaseTo(initDegree());
    }

    void standUp() {
        easeTo(initDegree());
    }

    virtual void startForwardTo(int targetDegree) {
        int degree = initDegree() - targetDegree;
        startEaseTo(max(degree, minDegree()));
    };

    virtual void forward(int targetDegree) {
        int degree = initDegree() - targetDegree;
        easeTo(max(degree, minDegree()));
    };

    virtual void startBackwardTo(int targetDegree) {
        int degree = initDegree() + targetDegree;
        startEaseTo(min(degree, maxDegree()));
    };

    virtual void backward(int targetDegree) {
        int degree = initDegree() + targetDegree;
        easeTo(min(degree, maxDegree()));
    };

    void setEasingType(uint_fast8_t aEasingType) const {
        ServoEasing::ServoEasingArray[servoIndex]->setEasingType(aEasingType);
    }

protected:
    String nickName;
    int servoIndex = -1;
    ServoEasing *tServoEasingObjectPtr;
};

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
#ifdef USE_PCA9685_SERVO_EXPANDER
        tServoEasingObjectPtr = new ServoEasing(aPCA9685I2CAddress);
#else
#error Define USE_PCA9685_SERVO_EXPANDER!
#endif
    }

    DefaultServoController(const String &nickName) {
        this->nickName = nickName;
        tServoEasingObjectPtr = new ServoEasing();
    };

    virtual ~DefaultServoController() = default;

    virtual void attach(int pinNo) {
        servoIndex = tServoEasingObjectPtr->attach(pinNo, initDegree(), msForServo0Degree(), msForServo180Degree());
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) Attached [Pin #%2d] [myServo #%2d] [Init %3d] [Min %3d] [Max %3d]",
                 &nickName, pinNo, servoIndex, initDegree(), msForServo0Degree(), msForServo180Degree());
    }

    virtual void setSpeed(uint_fast16_t speed) {
        tServoEasingObjectPtr->setSpeed(speed);
    };

    virtual int startEaseTo(int targetDegree) {
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) StartEaseTo %3d", &nickName, targetDegree);
        tServoEasingObjectPtr->startEaseTo(targetDegree);
        return tServoEasingObjectPtr->getEndMicrosecondsOrUnits();
    }

    virtual void easeTo(int targetDegree) {
        ESP_LOGI(DEFAULT_SERVO_TAG, "(%s) EaseTo %3d", &nickName, targetDegree);
        tServoEasingObjectPtr->easeTo(targetDegree);
    }

    void startStandUp() {
        startEaseTo(initDegree());
    }

    void standUp() {
        easeTo(initDegree());
    }

    int startForwardTo(int targetDegree) {
        int degree = initDegree() - targetDegree * (reverseDirection ? -1 : 1);
        return startEaseTo(max(degree, minDegree()));
    };


    int startBackwardTo(int targetDegree) {
        int degree = initDegree() + targetDegree * (reverseDirection ? -1 : 1);
        return startEaseTo(min(degree, maxDegree()));
    };

    void forward(int targetDegree) {
        int degree = initDegree() - targetDegree * (reverseDirection ? -1 : 1);
        easeTo(max(degree, minDegree()));
    };

    void backward(int targetDegree) {
        int degree = initDegree() + targetDegree * (reverseDirection ? -1 : 1);
        easeTo(min(degree, maxDegree()));
    };

protected:
    String nickName;
    int servoIndex = -1;
    ServoEasing *tServoEasingObjectPtr;
    bool reverseDirection = false;
};

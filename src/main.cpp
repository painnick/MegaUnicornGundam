#include <Arduino.h>

#include "common.h"
#include "controllers/Mp3Controller.h"
#include "MovementManager.h"

#include <Wire.h>

#include <Adafruit_NeoPixel.h>

#define MAIN_TAG "main"


#define PIN_STRIP_STAGE 18
#define STRIP_STAGE_SIZE 4
Adafruit_NeoPixel stripStage = Adafruit_NeoPixel(STRIP_STAGE_SIZE, PIN_STRIP_STAGE, NEO_GRB + NEO_KHZ800);

MovementManager movementManager;


void setup() {
    stripStage.setBrightness(255);
    for (int i = 0; i < STRIP_STAGE_SIZE; i++)
        stripStage.setPixelColor(i, 255, 63, 0);
    stripStage.show();

    ESP_LOGI(MAIN_TAG, "InitializeAndCheckI2CConnection...");

    Wire.begin();
    checkI2CConnection(PCA9685_DEFAULT_ADDRESS, &Serial);
    ESP_LOGI(MAIN_TAG, "I2C Connected");

    movementManager.attach();
    ESP_LOGI(MAIN_TAG, "Attached!");
    delay(2000);

    movementManager.initSpeed();
}

void loop() {
    for(int i = 0; i < 2; i ++) {
        movementManager.leftStep();

        movementManager.standUp();

        movementManager.rightStep();

        movementManager.standUp();
    }
    delay(1000);

    movementManager.headXY();

    delay(1000);

    movementManager.headZ();

    delay(1000 * 10);
}


#include "HaloSense.hpp"

#include <Arduino.h>

void HaloSense::onGesture(GestureType gesture) { Serial.print("Do noting"); }

void HaloSense::onUp() {
    switchLed();
    delay(1000);
}

void HaloSense::onDown() {
    switchLed();
    delay(1000);
}

void HaloSense::onLeft() { ledController.nextMode(); }

void HaloSense::onRight() { ledController.nextMode(); }

void HaloSense::onForward() { ledController.nextMode(); }

void HaloSense::onBackward() { ledController.nextMode(); }

void HaloSense::onClockwise() { ledController.nextMode(); }

void HaloSense::onAntiClockwise() { ledController.nextMode(); }

void HaloSense::onWave() { ledController.nextMode(); }

void HaloSense::switchLed() {
    if (isLedOn) {
        ledController.turnOffLed();
    } else {
        ledController.switchToMode(ledController.getLastMode());
    }
    isLedOn = !isLedOn;  // 状態を反転
}

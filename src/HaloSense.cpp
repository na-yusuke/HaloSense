#include "HaloSense.hpp"

#include <Arduino.h>

void HaloSense::onGesture(GestureType gesture) {
    Serial.println("onGesture: Do noting");
}

void HaloSense::onUp() { Serial.println("onUp: Do noting"); }

void HaloSense::onDown() { Serial.println("onDown: Do noting"); }

void HaloSense::onLeft() {
    Serial.println("onLeft: Previous Mode");
    led_controller_.previousMode();
}

void HaloSense::onRight() {
    Serial.println("onRight: Next Mode");
    led_controller_.nextMode();
}

void HaloSense::onForward() {
    Serial.println("onForward: Toggle LED");
    led_controller_.toggleLed();
}

void HaloSense::onBackward() { Serial.println("onBackward: Do noting"); }

void HaloSense::onClockwise() { Serial.println("onClockwise: Do noting"); }

void HaloSense::onAntiClockwise() {
    Serial.println("onAntiClockwise: Do noting");
}

void HaloSense::onWave() { Serial.println("onWave: Do noting"); }

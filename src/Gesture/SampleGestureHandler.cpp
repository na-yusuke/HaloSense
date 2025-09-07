#include "SampleGestureHandler.hpp"

#include <Arduino.h>

void SampleGestureHandler::onGesture(GestureType gesture) {
    Serial.print("Gesture detected: ");
    switch (gesture) {
        case GestureType::UP:
            Serial.println("UP");
            break;
        case GestureType::DOWN:
            Serial.println("DOWN");
            break;
        case GestureType::LEFT:
            Serial.println("LEFT");
            break;
        case GestureType::RIGHT:
            Serial.println("RIGHT");
            break;
        case GestureType::FORWARD:
            Serial.println("FORWARD");
            break;
        case GestureType::BACKWARD:
            Serial.println("BACKWARD");
            break;
        case GestureType::CLOCKWISE:
            Serial.println("CLOCKWISE");
            break;
        case GestureType::ANTI_CLOCKWISE:
            Serial.println("ANTI_CLOCKWISE");
            break;
        case GestureType::WAVE:
            Serial.println("WAVE");
            break;
        default:
            Serial.println("NONE");
            break;
    }
}

void SampleGestureHandler::onUp() {
    Serial.println("Custom UP action: Moving forward");
}

void SampleGestureHandler::onDown() {
    Serial.println("Custom DOWN action: Moving backward");
}

void SampleGestureHandler::onLeft() {
    Serial.println("Custom LEFT action: Turning left");
}

void SampleGestureHandler::onRight() {
    Serial.println("Custom RIGHT action: Turning right");
}

void SampleGestureHandler::onForward() {
    Serial.println("Custom FORWARD action: Accelerating");
}

void SampleGestureHandler::onBackward() {
    Serial.println("Custom BACKWARD action: Decelerating");
}

void SampleGestureHandler::onClockwise() {
    Serial.println("Custom CLOCKWISE action: Rotating clockwise");
}

void SampleGestureHandler::onAntiClockwise() {
    Serial.println("Custom ANTI_CLOCKWISE action: Rotating counter-clockwise");
}

void SampleGestureHandler::onWave() {
    Serial.println("Custom WAVE action: Hello gesture detected");
}
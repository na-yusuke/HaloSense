#include "GestureDetector.hpp"

bool GestureDetector::init() {
    Wire.setSCL(9);
    Wire.setSDA(8);
    if (Gesture.init()) {
        Serial.println("PAJ7620U2 initialization success");
        return true;
    } else {
        Serial.println("PAJ7620U2 initialization failed");
        return false;
    }
}

void GestureDetector::setGestureHandler(
    std::shared_ptr<IGestureHandler> handler) {
    gestureHandler = handler;
}

void GestureDetector::processGestures() {
    static unsigned long lastGestureCheckMs = 0;
    unsigned long currentTimeMs = millis();

    paj7620_gesture_t result;
    if (!Gesture.getResult(result)) {
        return;
    }
    if ((currentTimeMs - lastGestureCheckMs) < gestureIntervalMs) {
        return;
    }
    GestureType gesture = mapGesture(result);
    handleGesture(gesture);
    lastGestureCheckMs = currentTimeMs;
}

GestureType GestureDetector::mapGesture(paj7620_gesture_t rawGesture) {
    switch (rawGesture) {
        case UP:
            return GestureType::UP;
        case DOWN:
            return GestureType::DOWN;
        case LEFT:
            return GestureType::LEFT;
        case RIGHT:
            return GestureType::RIGHT;
        case PUSH:
            return GestureType::FORWARD;
        case POLL:
            return GestureType::BACKWARD;
        case CLOCKWISE:
            return GestureType::CLOCKWISE;
        case ANTI_CLOCKWISE:
            return GestureType::ANTI_CLOCKWISE;
        case WAVE:
            return GestureType::WAVE;
        default:
            return GestureType::NONE;
    }
}

void GestureDetector::handleGesture(GestureType gesture) {
    if (gestureHandler) {
        gestureHandler->onGesture(gesture);
    }

    switch (gesture) {
        case GestureType::UP:
            if (gestureHandler) gestureHandler->onUp();
            break;
        case GestureType::DOWN:
            if (gestureHandler) gestureHandler->onDown();
            break;
        case GestureType::LEFT:
            if (gestureHandler) gestureHandler->onLeft();
            break;
        case GestureType::RIGHT:
            if (gestureHandler) gestureHandler->onRight();
            break;
        case GestureType::FORWARD:
            if (gestureHandler) gestureHandler->onForward();
            break;
        case GestureType::BACKWARD:
            if (gestureHandler) gestureHandler->onBackward();
            break;
        case GestureType::CLOCKWISE:
            if (gestureHandler) gestureHandler->onClockwise();
            break;
        case GestureType::ANTI_CLOCKWISE:
            if (gestureHandler) gestureHandler->onAntiClockwise();
            break;
        case GestureType::WAVE:
            if (gestureHandler) gestureHandler->onWave();
            break;
        case GestureType::NONE:
        default:
            break;
    }
}

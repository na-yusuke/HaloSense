#include "GestureDetector.hpp"

#define GES_ENTRY_TIME 800
#define GES_QUIT_TIME 1000

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
    paj7620_gesture_t result;
    if (Gesture.getResult(result)) {
        GestureType gesture = mapGesture(result);
        handleGesture(gesture);
    }
    delay(100);
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
            callSecondaryGesture(GestureType::UP);
            break;
        case GestureType::DOWN:
            if (gestureHandler) gestureHandler->onDown();
            callSecondaryGesture(GestureType::DOWN);
            break;
        case GestureType::LEFT:
            if (gestureHandler) gestureHandler->onLeft();
            callSecondaryGesture(GestureType::LEFT);
            break;
        case GestureType::RIGHT:
            if (gestureHandler) gestureHandler->onRight();
            callSecondaryGesture(GestureType::RIGHT);
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

void GestureDetector::callSecondaryGesture(GestureType primaryGesture) {
    delay(GES_ENTRY_TIME);
    paj7620_gesture_t nextGesture;
    if (Gesture.getResult(nextGesture)) {
        GestureType secondaryGesture = mapGesture(nextGesture);
        if (secondaryGesture == GestureType::FORWARD ||
            secondaryGesture == GestureType::BACKWARD) {
            if (gestureHandler) {
                gestureHandler->onGesture(secondaryGesture);
                if (secondaryGesture == GestureType::FORWARD) {
                    gestureHandler->onForward();
                } else {
                    gestureHandler->onBackward();
                }
            }
            delay(GES_QUIT_TIME);
        }
    }
}
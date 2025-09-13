#include "GestureDetector.hpp"

bool GestureDetector::init() {
    Wire.setSCL(9);
    Wire.setSDA(8);
    if (gesture_.init()) {
        Serial.println("PAJ7620U2 initialization success");
        return true;
    } else {
        Serial.println("PAJ7620U2 initialization failed");
        return false;
    }
}

void GestureDetector::setGestureHandler(
    std::shared_ptr<IGestureHandler> handler) {
    gesture_handler_ = handler;
}

void GestureDetector::processGestures() {
    static uint32_t last_gesture_check_ms = 0;
    uint32_t current_time_ms = millis();

    paj7620_gesture_t result;
    if (!gesture_.getResult(result)) {
        return;
    }
    if ((current_time_ms - last_gesture_check_ms) < gesture_interval_ms_) {
        return;
    }
    GestureType gesture = mapGesture(result);
    handleGesture(gesture);
    last_gesture_check_ms = current_time_ms;
}

GestureType GestureDetector::mapGesture(paj7620_gesture_t raw_gesture) {
    switch (raw_gesture) {
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
    if (gesture_handler_) {
        gesture_handler_->onGesture(gesture);
    }

    switch (gesture) {
        case GestureType::UP:
            if (gesture_handler_) gesture_handler_->onUp();
            break;
        case GestureType::DOWN:
            if (gesture_handler_) gesture_handler_->onDown();
            break;
        case GestureType::LEFT:
            if (gesture_handler_) gesture_handler_->onLeft();
            break;
        case GestureType::RIGHT:
            if (gesture_handler_) gesture_handler_->onRight();
            break;
        case GestureType::FORWARD:
            if (gesture_handler_) gesture_handler_->onForward();
            break;
        case GestureType::BACKWARD:
            if (gesture_handler_) gesture_handler_->onBackward();
            break;
        case GestureType::CLOCKWISE:
            if (gesture_handler_) gesture_handler_->onClockwise();
            break;
        case GestureType::ANTI_CLOCKWISE:
            if (gesture_handler_) gesture_handler_->onAntiClockwise();
            break;
        case GestureType::WAVE:
            if (gesture_handler_) gesture_handler_->onWave();
            break;
        case GestureType::NONE:
        default:
            break;
    }
}

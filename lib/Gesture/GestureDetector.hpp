#ifndef GESTURE_DETECTOR_HPP
#define GESTURE_DETECTOR_HPP

#include <Wire.h>

#include <memory>

#include "Gesture.h"

enum class GestureType {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD,
    CLOCKWISE,
    ANTI_CLOCKWISE,
    WAVE,
    NONE
};

class IGestureHandler {
   public:
    virtual ~IGestureHandler() = default;
    virtual void onGesture(GestureType gesture) {}
    virtual void onUp() {}
    virtual void onDown() {}
    virtual void onLeft() {}
    virtual void onRight() {}
    virtual void onForward() {}
    virtual void onBackward() {}
    virtual void onClockwise() {}
    virtual void onAntiClockwise() {}
    virtual void onWave() {}
};

class GestureDetector {
   public:
    GestureDetector(unsigned long intervalMs) : gestureIntervalMs(intervalMs) {
        gestureHandler = nullptr;
    }
    bool init();
    void processGestures();
    void setGestureHandler(std::shared_ptr<IGestureHandler> handler);

   private:
    GestureType mapGesture(paj7620_gesture_t rawGesture);
    void handleGesture(GestureType gesture);

    paj7620 Gesture;
    std::shared_ptr<IGestureHandler> gestureHandler;
    unsigned long gestureIntervalMs;
};

#endif  // GESTURE_DETECTOR_HPP

#ifndef SAMPLE_GESTURE_HANDLER_HPP
#define SAMPLE_GESTURE_HANDLER_HPP

#include "GestureDetector.hpp"

class SampleGestureHandler : public IGestureHandler {
   public:
    void onGesture(GestureType gesture) override;
    void onUp() override;
    void onDown() override;
    void onLeft() override;
    void onRight() override;
    void onForward() override;
    void onBackward() override;
    void onClockwise() override;
    void onAntiClockwise() override;
    void onWave() override;
};

#endif  // SAMPLE_GESTURE_HANDLER_HPP
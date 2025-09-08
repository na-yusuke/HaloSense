#ifndef HALO_SENSE_HPP
#define HALO_SENSE_HPP

#include <GestureDetector.hpp>
#include <LedController.hpp>

class HaloSense : public IGestureHandler {
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

    void updateLed() { ledController.update(); }

   private:
    LedController ledController;
};

#endif  // HALO_SENSE_HPP

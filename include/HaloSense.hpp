#ifndef HALO_SENSE_HPP
#define HALO_SENSE_HPP

#include <GestureDetector.hpp>
#include <LedController.hpp>
#include <LumenMeter.hpp>

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

    void adjustLedBrightnessByAmbientLight() {
        int32_t lumenValue = lumenMeter.readLumenValue();
        if (lumenValue == lastLumenValue) return;
        lastLumenValue = lumenValue;
        ledController.setBrightness(map(lumenValue, 0, 1023, 50, 220));
    }
    void updateLed() { ledController.update(); }

   private:
    LedController ledController;
    LumenMeter lumenMeter;

    int32_t lastLumenValue = -1;
};

#endif  // HALO_SENSE_HPP

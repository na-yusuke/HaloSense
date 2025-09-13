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
        int32_t lumen_value_ = lumen_meter_.readLumenValue();
        if (lumen_value_ == last_lumen_value_) return;
        last_lumen_value_ = lumen_value_;
        led_controller_.setBrightness(map(lumen_value_, 0, 1023, 50, 220));
    }
    void updateLed() { led_controller_.update(); }

   private:
    LedController led_controller_;
    LumenMeter lumen_meter_;

    int32_t last_lumen_value_ = -1;
};

#endif  // HALO_SENSE_HPP

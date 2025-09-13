#ifndef LUMEN_METER_HPP
#define LUMEN_METER_HPP

#include <Wire.h>

class LumenMeter {
   public:
    LumenMeter(uint32_t interval_ms = 1000) : lumen_interval_ms_(interval_ms) {}

    void setAnalogPin(int32_t pin) { analog_pin_ = pin; }
    uint8_t getAnalogPin() const { return analog_pin_; }
    uint8_t getLastLumenValue() const { return lumen_value_; }
    int32_t readLumenValue() {
        static uint32_t last_gesture_check_ms = 0;
        uint32_t current_time_ms = millis();

        if ((current_time_ms - last_gesture_check_ms) < lumen_interval_ms_) {
            return lumen_value_;
        }
        lumen_value_ = analogRead(analog_pin_);
        last_gesture_check_ms = current_time_ms;

        return lumen_value_;
    }

   private:
    int32_t lumen_value_ = 0;
    uint32_t lumen_interval_ms_;
    uint8_t analog_pin_ = A0;
};

#endif  // LUMEN_METER_HPP

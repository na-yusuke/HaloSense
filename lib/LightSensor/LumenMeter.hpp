#ifndef LUMEN_METER_HPP
#define LUMEN_METER_HPP

#include <Wire.h>

class LumenMeter {
   public:
    LumenMeter(uint32_t intervalMs = 1000) : lumenIntervalMs(intervalMs) {}

    void setAnalogPin(int32_t pin) { analogPin = pin; }
    uint8_t getAnalogPin() const { return analogPin; }
    uint8_t getLastLumenValue() const { return lumenValue; }
    int32_t readLumenValue() {
        static uint32_t lastGestureCheckMs = 0;
        uint32_t currentTimeMs = millis();

        if ((currentTimeMs - lastGestureCheckMs) < lumenIntervalMs) {
            return lumenValue;
        }
        lumenValue = analogRead(analogPin);
        lastGestureCheckMs = currentTimeMs;

        return lumenValue;
    }

   private:
    int32_t lumenValue = 0;
    uint32_t lumenIntervalMs;
    uint8_t analogPin = A0;
};

#endif  // LUMEN_METER_HPP

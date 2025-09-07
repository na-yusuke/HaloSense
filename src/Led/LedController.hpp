#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include <FastLED.h>

#define LED_TYPE SK6812
#define LED_PIN 0
#define LED_COUNT 300
#define BRIGHTNESS 10
#define COLOR_ORDER GRB

class LedController {
   public:
    LedController() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
        FastLED.setBrightness(BRIGHTNESS);
    }

    void setColor(CRGB color) {
        for (int i = 0; i < LED_COUNT; i++) {
            leds[i] = color;
        }
        FastLED.show();
    }

    void clear() {
        FastLED.clear();
        FastLED.show();
    }

    void dotLineFlow(CRGB color, int speed = 80);
    void rainbowFlow(int speed = 30);
    void smoothFlow(CRGB color, int speed = 60, int trailLength = 30);
    void multiTrailFlow(CRGB color, int speed = 60, int trailLength = 30, int numTrails = 3, int spacing = 100);
    void fireEffect(int speed = 100);
    void waveEffect(CRGB color, int speed = 50, int waveLength = 20);

   private:
    void resetLeds() {
        for (int i = 0; i < LED_COUNT; i++) {
            leds[i] = CRGB::Black;
        }
    }

    CRGB leds[LED_COUNT];
};

#endif  // LED_CONTROLLER_HPP

#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include <FastLED.h>

#define LED_TYPE SK6812
#define LED_PIN 0
#define LED_COUNT 300
#define BRIGHTNESS 10
#define COLOR_ORDER GRB

enum class LedMode {
    SOLID_COLOR,
    RAINBOW_FLOW,
    SMOOTH_FLOW,
    MULTI_TRAIL_FLOW,
    FIRE_EFFECT,
    WAVE_EFFECT,
    OFF
};

class LedController {
   public:
    LedController() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
        FastLED.setBrightness(BRIGHTNESS);
        lastMode = LedMode::OFF;
        lastColor = CRGB::White;
    }

    void setColor(CRGB color);
    void relax() { setColor(CRGB::GreenYellow); }
    void rainbowFlow(int speed = 30);
    void smoothFlow(CRGB color, int speed = 60, int trailLength = 30);
    void multiTrailFlow(CRGB color, int speed = 60, int trailLength = 30,
                        int numTrails = 3, int spacing = 100);
    void fireEffect(int speed = 100);
    void waveEffect(CRGB color, int speed = 50, int waveLength = 20);
    void turnOffLed();
    void restoreLastMode();
    void switchToMode(LedMode mode);

    LedMode getLastMode() const { return lastMode; }
    CRGB getLastColor() const { return lastColor; }
    LedMode getNextMode() const {
        switch (lastMode) {
            case LedMode::SOLID_COLOR:
                return LedMode::RAINBOW_FLOW;
            case LedMode::RAINBOW_FLOW:
                return LedMode::SMOOTH_FLOW;
            case LedMode::SMOOTH_FLOW:
                return LedMode::MULTI_TRAIL_FLOW;
            case LedMode::MULTI_TRAIL_FLOW:
                return LedMode::FIRE_EFFECT;
            case LedMode::FIRE_EFFECT:
                return LedMode::WAVE_EFFECT;
            case LedMode::WAVE_EFFECT:
                return LedMode::SOLID_COLOR;
            case LedMode::OFF:
                return LedMode::SOLID_COLOR;
            default:
                return LedMode::SOLID_COLOR;
        }
    }
    void nextMode() { switchToMode(getNextMode()); }

   private:
    void resetLeds() {
        for (int i = 0; i < LED_COUNT; i++) {
            leds[i] = CRGB::Black;
        }
    }

    CRGB leds[LED_COUNT];
    LedMode lastMode;
    CRGB lastColor;
};

#endif  // LED_CONTROLLER_HPP

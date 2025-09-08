#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include <FastLED.h>

#define LED_TYPE SK6812
#define LED_PIN 0
#define LED_COUNT 300
#define BRIGHTNESS 10
#define COLOR_ORDER GRB

// LED更新間隔（ミリ秒）
#define LED_UPDATE_INTERVAL_MS 50

enum class LedMode {
    RELAX = 0,
    RAINBOW_FLOW = 1,
    MULTI_TRAIL_FLOW = 2,
    FIRE_EFFECT = 3,
    WAVE_EFFECT = 4,
    OFF = 5,

    // 最後のアクティブモード（OFFを除く）
    LAST_ACTIVE_MODE = WAVE_EFFECT
};

class LedController {
   public:
    LedController() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
        FastLED.setBrightness(BRIGHTNESS);
        lastMode = LedMode::OFF;
        isLedOn = false;
    }

    void setColor(CRGB color);
    void relax();
    void rainbowFlow(int speed = 30);
    void multiTrailFlow(CRGB color, int speed = 60, int trailLength = 30,
                        int numTrails = 3, int spacing = 100);
    void fireEffect(int speed = 100);
    void waveEffect(CRGB color, int speed = 50, int waveLength = 20);
    void turnOffLed();
    void switchToMode(LedMode mode);
    void update();
    void toggleLed();
    bool isLedEnabled() const { return isLedOn; }

    LedMode getModeAt(int direction) const;
    LedMode getLastMode() const { return lastMode; }
    void nextMode() { switchToMode(getModeAt(1)); }
    void previousMode() { switchToMode(getModeAt(-1)); }

   private:
    void resetLeds() {
        for (int i = 0; i < LED_COUNT; i++) {
            leds[i] = CRGB::Black;
        }
    }

    CRGB leds[LED_COUNT];
    LedMode lastMode;
    unsigned long lastUpdate = 0;
    bool isLedOn;
};

#endif  // LED_CONTROLLER_HPP

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
        turnOffLed();
    }

    // LEDエフェクト系メソッド
    void setColor(CRGB color);
    void relax();
    void rainbowFlow(int32_t speed = 30);
    void multiTrailFlow(CRGB color, int32_t speed = 60,
                        int32_t trailLength = 30, int32_t numTrails = 3,
                        int32_t spacing = 100);
    void fireEffect(int32_t speed = 100);
    void waveEffect(CRGB color, int32_t speed = 50, int32_t waveLength = 20);

    // LED制御系メソッド
    void turnOffLed();
    void switchToMode(LedMode mode);
    void update();
    void toggleLed();
    void setBrightness(int32_t brightness) {
        FastLED.setBrightness(brightness);
    }

    bool isLedEnabled() const { return isLedOn; }
    LedMode getLastMode() const { return lastMode; }
    LedMode getModeAt(int32_t direction) const;
    void nextMode();
    void previousMode();

   private:
    void resetLeds();

    CRGB leds[LED_COUNT];
    LedMode lastMode;
    uint32_t lastUpdate = 0;
    bool isLedOn;
};

#endif  // LED_CONTROLLER_HPP

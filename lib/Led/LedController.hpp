#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include <FastLED.h>

#include <vector>

#define LED_TYPE SK6812
#define LED_PIN 0
#define COLOR_ORDER GRB

enum class LedMode {
    RELAX = 0,
    RAINBOW_FLOW = 1,
    MULTI_TRAIL_FLOW = 2,
    FIRE_EFFECT = 3,
    WAVE_EFFECT = 4,
    OFF = 5,

    // Last active mode (excluding OFF)
    LAST_ACTIVE_MODE = WAVE_EFFECT
};

class LedController {
   public:
    LedController(uint16_t led_count = 300, uint16_t brightness = 10,
                  uint32_t interval_ms = 50)
        : led_interval_ms_(interval_ms),
          led_count_(led_count),
          leds_(led_count) {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds_.data(),
                                                        led_count_);
        FastLED.setBrightness(brightness);
        last_mode_ = LedMode::OFF;
        is_led_on_ = false;
        turnOffLed();
    }

    // LED effect methods
    void setColor(CRGB color);
    void relax();
    void rainbowFlow(int32_t speed = 30);
    void multiTrailFlow(CRGB color, int32_t speed = 60,
                        int32_t trail_length = 30, int32_t num_trails = 3,
                        int32_t spacing = 100);
    void fireEffect(int32_t speed = 100);
    void waveEffect(CRGB color, int32_t speed = 50, int32_t wave_length = 20);

    // LED control methods
    void turnOffLed();
    void switchToMode(LedMode mode);
    void update();
    void toggleLed();
    void setBrightness(int32_t brightness) {
        FastLED.setBrightness(brightness);
    }

    bool isLedEnabled() const { return is_led_on_; }
    LedMode getLastMode() const { return last_mode_; }
    LedMode getModeAt(int32_t direction) const;
    void nextMode();
    void previousMode();

   private:
    void resetLeds();

    std::vector<CRGB> leds_;
    LedMode last_mode_;
    uint32_t led_interval_ms_;
    uint32_t last_update_ = 0;
    uint16_t led_count_;
    bool is_led_on_;
};

#endif  // LED_CONTROLLER_HPP

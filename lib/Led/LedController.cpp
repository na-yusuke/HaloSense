#include "LedController.hpp"

void LedController::setColor(CRGB color) {
    for (int32_t i = 0; i < led_count_; i++) {
        leds_[i] = color;
    }
    FastLED.show();
}

void LedController::relax() {
    if (last_mode_ != LedMode::RELAX) last_mode_ = LedMode::RELAX;
    setColor(CRGB::GreenYellow);
}

void LedController::rainbowFlow(int32_t speed) {
    if (last_mode_ != LedMode::RAINBOW_FLOW) last_mode_ = LedMode::RAINBOW_FLOW;

    static uint8_t hue = 0;
    for (int32_t i = 0; i < led_count_; i++) {
        leds_[i] = CHSV((hue + i * 2) % 256, 255, 255);
    }

    FastLED.show();
    hue += 2;
    delay(speed);
}

void LedController::multiTrailFlow(CRGB color, int32_t speed,
                                   int32_t trail_length, int32_t num_trails,
                                   int32_t spacing) {
    if (last_mode_ != LedMode::MULTI_TRAIL_FLOW)
        last_mode_ = LedMode::MULTI_TRAIL_FLOW;

    static int32_t head = 0;
    // Gradually fade the tail
    for (int32_t i = 0; i < led_count_; i++) {
        leds_[i].fadeToBlackBy(15);
    }

    // Draw multiple trails
    for (int32_t trail = 0; trail < num_trails; trail++) {
        int32_t trail_head = (head + trail * spacing) % led_count_;

        // Draw each trail
        for (int32_t i = 0; i < trail_length; i++) {
            int32_t pos = (trail_head - i + led_count_) % led_count_;
            float brightness = (float)(trail_length - i) / trail_length;

            // Add to existing brightness (adjust brightness on overlap)
            CRGB newColor = CRGB(color.r * brightness, color.g * brightness,
                                 color.b * brightness);
            leds_[pos] = leds_[pos] + newColor;
        }
    }

    FastLED.show();
    head = (head + 1) % led_count_;
    delay(speed);
}

void LedController::fireEffect(int32_t speed) {
    if (last_mode_ != LedMode::FIRE_EFFECT) last_mode_ = LedMode::FIRE_EFFECT;

    for (int32_t i = 0; i < led_count_; i++) {
        int32_t flickerRed = random(100, 255);
        int32_t flickerGreen = random(0, flickerRed / 3);
        leds_[i] = CRGB(flickerRed, flickerGreen, 0);
    }

    FastLED.show();
    delay(speed);
}

void LedController::waveEffect(CRGB color, int32_t speed, int32_t wave_length) {
    if (last_mode_ != LedMode::WAVE_EFFECT) last_mode_ = LedMode::WAVE_EFFECT;

    static int32_t pos = 0;
    resetLeds();
    for (int32_t i = 0; i < wave_length; i++) {
        int32_t led_index = (pos + i) % led_count_;
        float brightness = sin((float)i / wave_length * PI);
        leds_[led_index] = CRGB(color.r * brightness, color.g * brightness,
                                color.b * brightness);
    }

    FastLED.show();
    pos = (pos + 1) % led_count_;
    delay(speed);
}

void LedController::turnOffLed() {
    resetLeds();
    FastLED.show();
}

void LedController::switchToMode(LedMode mode) {
    resetLeds();
    last_mode_ = mode;
    last_update_ = 0;  // Update immediately
}

void LedController::update() {
    uint32_t current_time_ms = millis();
    if (!is_led_on_ || (current_time_ms - last_update_) < led_interval_ms_)
        return;  // Don't update when LED is OFF
    last_update_ = current_time_ms;

    switch (last_mode_) {
        case LedMode::RELAX:
            relax();
            break;
        case LedMode::RAINBOW_FLOW:
            rainbowFlow(0);
            break;
        case LedMode::MULTI_TRAIL_FLOW:
            multiTrailFlow(CRGB::MediumSpringGreen, 0);
            break;
        case LedMode::FIRE_EFFECT:
            fireEffect(0);
            break;
        case LedMode::WAVE_EFFECT:
            waveEffect(CRGB::Yellow, 0);
            break;
        case LedMode::OFF:
            break;
    }
}

void LedController::toggleLed() {
    if (is_led_on_) {
        turnOffLed();
    } else {
        if (last_mode_ == LedMode::OFF) {
            last_mode_ = LedMode::RELAX;
        }
        last_update_ = 0;  // Update immediately
    }
    is_led_on_ = !is_led_on_;
}

LedMode LedController::getModeAt(int32_t direction) const {
    const int32_t num_active_modes =
        static_cast<int32_t>(LedMode::LAST_ACTIVE_MODE) + 1;

    int32_t current_index = static_cast<int32_t>(last_mode_);
    if (last_mode_ == LedMode::OFF) {
        current_index = static_cast<int32_t>(LedMode::RELAX);
    }

    int32_t new_index =
        (current_index + direction + num_active_modes) % num_active_modes;
    return static_cast<LedMode>(new_index);
}

void LedController::nextMode() { switchToMode(getModeAt(1)); }

void LedController::previousMode() { switchToMode(getModeAt(-1)); }

void LedController::resetLeds() {
    for (int32_t i = 0; i < led_count_; i++) {
        leds_[i] = CRGB::Black;
    }
}
#include "LedController.hpp"

void LedController::setColor(CRGB color) {
    for (int32_t i = 0; i < LED_COUNT; i++) {
        leds[i] = color;
    }
    FastLED.show();
}

void LedController::relax() {
    if (lastMode != LedMode::RELAX) lastMode = LedMode::RELAX;
    setColor(CRGB::GreenYellow);
}

void LedController::rainbowFlow(int32_t speed) {
    if (lastMode != LedMode::RAINBOW_FLOW) lastMode = LedMode::RAINBOW_FLOW;

    static uint8_t hue = 0;
    for (int32_t i = 0; i < LED_COUNT; i++) {
        leds[i] = CHSV((hue + i * 2) % 256, 255, 255);
    }

    FastLED.show();
    hue += 2;
    delay(speed);
}

void LedController::multiTrailFlow(CRGB color, int32_t speed,
                                   int32_t trailLength, int32_t numTrails,
                                   int32_t spacing) {
    if (lastMode != LedMode::MULTI_TRAIL_FLOW)
        lastMode = LedMode::MULTI_TRAIL_FLOW;

    static int32_t head = 0;
    // 尾を徐々に暗くする
    for (int32_t i = 0; i < LED_COUNT; i++) {
        leds[i].fadeToBlackBy(15);
    }

    // 複数のトレイルを描画
    for (int32_t trail = 0; trail < numTrails; trail++) {
        int32_t trailHead = (head + trail * spacing) % LED_COUNT;

        // 各トレイルの描画
        for (int32_t i = 0; i < trailLength; i++) {
            int32_t pos = (trailHead - i + LED_COUNT) % LED_COUNT;
            float brightness = (float)(trailLength - i) / trailLength;

            // 既存の明度と加算（重複時の明るさ調整）
            CRGB newColor = CRGB(color.r * brightness, color.g * brightness,
                                 color.b * brightness);
            leds[pos] = leds[pos] + newColor;
        }
    }

    FastLED.show();
    head = (head + 1) % LED_COUNT;
    delay(speed);
}

void LedController::fireEffect(int32_t speed) {
    if (lastMode != LedMode::FIRE_EFFECT) lastMode = LedMode::FIRE_EFFECT;

    for (int32_t i = 0; i < LED_COUNT; i++) {
        int32_t flickerRed = random(100, 255);
        int32_t flickerGreen = random(0, flickerRed / 3);
        leds[i] = CRGB(flickerRed, flickerGreen, 0);
    }

    FastLED.show();
    delay(speed);
}

void LedController::waveEffect(CRGB color, int32_t speed, int32_t waveLength) {
    if (lastMode != LedMode::WAVE_EFFECT) lastMode = LedMode::WAVE_EFFECT;

    static int32_t pos = 0;
    resetLeds();
    for (int32_t i = 0; i < waveLength; i++) {
        int32_t ledIndex = (pos + i) % LED_COUNT;
        float brightness = sin((float)i / waveLength * PI);
        leds[ledIndex] = CRGB(color.r * brightness, color.g * brightness,
                              color.b * brightness);
    }

    FastLED.show();
    pos = (pos + 1) % LED_COUNT;
    delay(speed);
}

void LedController::turnOffLed() {
    resetLeds();
    FastLED.show();
}

void LedController::switchToMode(LedMode mode) {
    resetLeds();
    lastMode = mode;
    lastUpdate = 0;  // 即座に更新
}

void LedController::update() {
    uint32_t currentTimeMs = millis();
    if (!isLedOn || (currentTimeMs - lastUpdate) < LED_UPDATE_INTERVAL_MS)
        return;  // LED OFF時は更新しない
    lastUpdate = currentTimeMs;

    switch (lastMode) {
        case LedMode::RELAX:
            relax();
            break;
        case LedMode::RAINBOW_FLOW:
            rainbowFlow(0);
            break;
        case LedMode::MULTI_TRAIL_FLOW:
            multiTrailFlow(CRGB::Purple, 0);
            break;
        case LedMode::FIRE_EFFECT:
            fireEffect(0);
            break;
        case LedMode::WAVE_EFFECT:
            waveEffect(CRGB::Cyan, 0);
            break;
        case LedMode::OFF:
            break;
    }
}

void LedController::toggleLed() {
    if (isLedOn) {
        turnOffLed();
    } else {
        if (lastMode == LedMode::OFF) {
            lastMode = LedMode::RELAX;
        }
        lastUpdate = 0;  // 即座に更新
    }
    isLedOn = !isLedOn;
}

LedMode LedController::getModeAt(int32_t direction) const {
    const int32_t numActiveModes =
        static_cast<int32_t>(LedMode::LAST_ACTIVE_MODE) + 1;

    int32_t currentIndex = static_cast<int32_t>(lastMode);
    if (lastMode == LedMode::OFF) {
        currentIndex = static_cast<int32_t>(LedMode::RELAX);
    }

    int32_t newIndex =
        (currentIndex + direction + numActiveModes) % numActiveModes;
    return static_cast<LedMode>(newIndex);
}

void LedController::nextMode() { switchToMode(getModeAt(1)); }

void LedController::previousMode() { switchToMode(getModeAt(-1)); }

void LedController::resetLeds() {
    for (int32_t i = 0; i < LED_COUNT; i++) {
        leds[i] = CRGB::Black;
    }
}
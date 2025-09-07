#include "LedController.hpp"

void LedController::dotLineFlow(CRGB color, int speed) {
    static int ripplePos = 0;
    const int rippleWidth = 15;

    resetLeds();

    for (int i = 0; i < LED_COUNT; i++) {
        int distance = abs(i - ripplePos);
        if (distance < rippleWidth) {
            float brightness = 1.0 - (float)distance / rippleWidth;
            leds[i] = CRGB(color.r * brightness, color.g * brightness,
                           color.b * brightness);
        }
    }

    FastLED.show();
    ripplePos = (ripplePos + 1) % LED_COUNT;
    delay(speed);
}

void LedController::rainbowFlow(int speed) {
    static uint8_t hue = 0;

    for (int i = 0; i < LED_COUNT; i++) {
        leds[i] = CHSV((hue + i * 2) % 256, 255, 255);
    }

    FastLED.show();
    hue += 2;
    delay(speed);
}

void LedController::smoothFlow(CRGB color, int speed, int trailLength) {
    static int head = 0;

    // 尾を徐々に暗くする
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].fadeToBlackBy(20);
    }

    // 新しい頭部を描画
    for (int i = 0; i < trailLength; i++) {
        int pos = (head - i + LED_COUNT) % LED_COUNT;
        float brightness = (float)(trailLength - i) / trailLength;
        leds[pos] = CRGB(color.r * brightness, color.g * brightness,
                         color.b * brightness);
    }

    FastLED.show();
    head = (head + 1) % LED_COUNT;
    delay(speed);
}

void LedController::multiTrailFlow(CRGB color, int speed, int trailLength, int numTrails, int spacing) {
    static int head = 0;

    // 尾を徐々に暗くする
    for (int i = 0; i < LED_COUNT; i++) {
        leds[i].fadeToBlackBy(15);
    }

    // 複数のトレイルを描画
    for (int trail = 0; trail < numTrails; trail++) {
        int trailHead = (head + trail * spacing) % LED_COUNT;
        
        // 各トレイルの描画
        for (int i = 0; i < trailLength; i++) {
            int pos = (trailHead - i + LED_COUNT) % LED_COUNT;
            float brightness = (float)(trailLength - i) / trailLength;
            
            // 既存の明度と加算（重複時の明るさ調整）
            CRGB newColor = CRGB(color.r * brightness, color.g * brightness, color.b * brightness);
            leds[pos] = leds[pos] + newColor;
        }
    }

    FastLED.show();
    head = (head + 1) % LED_COUNT;
    delay(speed);
}

void LedController::fireEffect(int speed) {
    for (int i = 0; i < LED_COUNT; i++) {
        int flickerRed = random(100, 255);
        int flickerGreen = random(0, flickerRed / 3);
        leds[i] = CRGB(flickerRed, flickerGreen, 0);
    }

    FastLED.show();
    delay(speed);
}

void LedController::waveEffect(CRGB color, int speed, int waveLength) {
    static int pos = 0;

    resetLeds();

    for (int i = 0; i < waveLength; i++) {
        int ledIndex = (pos + i) % LED_COUNT;
        float brightness = sin((float)i / waveLength * PI);
        leds[ledIndex] = CRGB(color.r * brightness, color.g * brightness,
                              color.b * brightness);
    }

    FastLED.show();
    pos = (pos + 1) % LED_COUNT;
    delay(speed);
}

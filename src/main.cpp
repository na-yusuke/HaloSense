#include <memory>

#include "Gesture/GestureDetector.hpp"
#include "HaloSense.hpp"

GestureDetector gestureDetector;
std::shared_ptr<HaloSense> handler;

void setup() {
    Serial.begin(115200);
    handler = std::make_shared<HaloSense>();

    if (gestureDetector.init()) {
        Serial.println("Please input your gestures:");
        Serial.println("UP/DOWN: Switch LED ON/OFF");
        Serial.println(
            "LEFT/RIGHT/FORWARD/BACKWARD/CLOCKWISE/ANTI_CLOCKWISE/WAVE: Change "
            "LED Mode");
    } else {
        Serial.println("GestureDetector initialization failed");
    }

    gestureDetector.setGestureHandler(handler);
}

void loop() {
    // ジェスチャー処理の実行
    gestureDetector.processGestures();
    // LEDエフェクト更新
    handler->updateLed();
}

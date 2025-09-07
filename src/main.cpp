#include <memory>

#include "Gesture/GestureDetector.hpp"
#include "Gesture/SampleGestureHandler.hpp"

GestureDetector gestureDetector;
std::shared_ptr<SampleGestureHandler> handler;

void setup() {
    handler = std::make_shared<SampleGestureHandler>();

    if (gestureDetector.init()) {
        Serial.println("Please input your gestures:\n");
    } else {
        Serial.println("GestureDetector initialization failed");
    }

    // ハンドラーの設定（依存性の注入）
    gestureDetector.setGestureHandler(handler);
}

void loop() {
    // ジェスチャー処理の実行
    gestureDetector.processGestures();
}

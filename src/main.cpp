#include <GestureDetector.hpp>
#include <LumenMeter.hpp>
#include <memory>

#include "HaloSense.hpp"

GestureDetector gesture_detector(400);
std::shared_ptr<HaloSense> handler;

void setup() {
    Serial.begin(115200);
    handler = std::make_shared<HaloSense>();

    if (gesture_detector.init()) {
        Serial.println("Please input your gestures:");
        Serial.println("UP/DOWN: Switch LED ON/OFF");
        Serial.println(
            "LEFT/RIGHT/FORWARD/BACKWARD/CLOCKWISE/ANTI_CLOCKWISE/WAVE: Change "
            "LED Mode");
    } else {
        Serial.println("GestureDetector initialization failed");
    }

    gesture_detector.setGestureHandler(handler);
}

void loop() {
    // Execute gesture processing
    gesture_detector.processGestures();
    // Read ambient light sensor value and adjust LED brightness
    handler->adjustLedBrightnessByAmbientLight();
    // Update LED effects
    handler->updateLed();
}

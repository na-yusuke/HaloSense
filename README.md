# HaloSense

Interactive LED System with Gesture Control

https://github.com/user-attachments/assets/b540b3bd-d70b-45e4-98d5-3e798b2ce873

## 🌍 Environment

### Hardware Requirements

#### Components

- Raspberry Pi Pico ([Purchase Link](https://www.switch-science.com/products/6900))
- Grove Shield for Pi Pico V1.0 ([Purchase Link](https://www.switch-science.com/products/7109))
- Grove - Gesture V1.0 ([Purchase Link](https://www.switch-science.com/products/2645))
- Grove - Light Sensor v1.2 ([Purchase Link](https://www.switch-science.com/products/3284))
- WS2812B LED Strip ([Purchase Link](https://www.btf-lighting.com/en-intl/products/ws2812b-led-pixel-strip-rgbic-addressable))

#### Connection Configuration

```txt
Raspberry Pi Pico with Grove Shield:
├── I2C0 → Grove - Gesture V1.0 (PAJ7620U2)
├── A0   → Grove - Light Sensor v1.2
├── GP0  → WS2812B LED Strip
└── USB  → PC or Power Supply
```

| <img src=/image/raspberrypi_pico.jpg width= "300px" > | <img src=/image/led_strip.jpg width= "300px" > | <img src=/image/gesture_sensor.jpg width= "300px" > | <img src=/image/lumen_sensor.jpg width= "300px" > |
| :----: | :----: | :----: | :----: |
| Raspberry Pi Pico | LED Strip | Gesture Sensor | Light Sensor |

### Software Requirements

#### Development Environment

- OS
  - Windows 10/11
- IDE
  - PlatformIO
  - VSCode (Recommended)

#### Dependencies

```ini
lib_deps = 
 seeed-studio/Grove Gesture@^2.1.0
 fastled/FastLED@^3.10.1
```

## 🚀 Setup

### 1. Install Required Tools

- Install [PlatformIO](https://platformio.org/) IDE extension for VSCode

### 2. Clone Repository

```bash
$ git clone https://github.com/na-yusuke/HaloSense.git
or
$ git clone git@github.com:na-yusuke/HaloSense.git
```

### 3. Build

```bash
$ C:\Users\<user>\.platformio\penv\Scripts\platformio.exe run --environment pico
```

- You can also build from VSCode PlatformIO IDE.

### 4. Upload

```bash
$ C:\Users\<user>\.platformio\penv\Scripts\platformio.exe run --target upload --environment pico
```

- You can also upload from VSCode PlatformIO IDE.

### 5. Start Serial Monitor

```bash
$ C:\Users\<user>\.platformio\penv\Scripts\platformio.exe device monitor --environment pico
```

- You can also start serial monitor from VSCode PlatformIO IDE.

## 🎮 Usage

### Gesture Control

| Gesture | Action |
|---------|--------|
| **LEFT** | Switch to previous LED effect |
| **RIGHT** | Switch to next LED effect |  
| **FORWARD** | Toggle LED ON/OFF |
| UP/DOWN/BACKWARD/CLOCKWISE/ANTI_CLOCKWISE/WAVE | Not used |

### LED Effect Modes

#### RELAX - Fixed green-yellow color

https://github.com/user-attachments/assets/98735359-6b4d-485f-8619-0da2b905b934

#### RAINBOW_FLOW - Flowing rainbow effect

https://github.com/user-attachments/assets/b540b3bd-d70b-45e4-98d5-3e798b2ce873

#### MULTI_TRAIL_FLOW - Multiple light trails following effect

https://github.com/user-attachments/assets/99d7cd5b-fad2-463a-b2bc-c7e4c578b8e0

#### FIRE_EFFECT - Flame-like flickering effect

https://github.com/user-attachments/assets/8895ab52-2fd1-48eb-9dab-5813eb820794

#### WAVE_EFFECT - Wave pattern effect

https://github.com/user-attachments/assets/32dad7a4-d0aa-4334-b5df-adb5c8f35909

## 📚 References

- [Grove - Gesture V1.0](https://wiki.seeedstudio.com/Grove-Gesture_v1.0/)
- [Grove - Light Sensor](https://wiki.seeedstudio.com/Grove-Light_Sensor/)
- [Grove Shield for Pi Pico v1.0 - Expansion board with connectors for connecting Grove devices](https://sanuki-tech.net/and-more/2022/seeed-grove-shield-for-pi-pico/)
- [【Arduino】Raspberry Pi Pico をArduinoでプログラミング！LEDを光らせよう。](https://karakuri-musha.com/inside-technology/arduino-raspberrypi-pico-ledstrip01/)

## 💡 Motivation for it

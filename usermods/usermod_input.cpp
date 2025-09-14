/*
 * usermod_input.cpp
 * Simple input usermod for buttons and analog joystick
 * for WLED on Waveshare ESP32-C6 with LCD.
 */

#include "wled.h"

#ifdef USERMOD_INPUT

class UsermodInput : public Usermod {
private:
  // Button pins (change these if you wire differently!)
  const int BTN_NEXT_EFFECT = 2;   // example GPIO for "next effect"
  const int BTN_NEXT_PALETTE = 3;  // example GPIO for "next palette"
  const int BTN_BRIGHTNESS = 4;    // example GPIO for "brightness step"

  // Joystick pins (analog input)
  const int JOY_X = 5;   // ADC pin X
  const int JOY_Y = 6;   // ADC pin Y

  unsigned long lastRead = 0;
  const unsigned long interval = 250; // read every 250ms

public:
  void setup() {
    pinMode(BTN_NEXT_EFFECT, INPUT_PULLUP);
    pinMode(BTN_NEXT_PALETTE, INPUT_PULLUP);
    pinMode(BTN_BRIGHTNESS, INPUT_PULLUP);
  }

  void loop() {
    if (millis() - lastRead < interval) return;
    lastRead = millis();

    // --- Buttons ---
    if (digitalRead(BTN_NEXT_EFFECT) == LOW) {
      effectCurrent = (effectCurrent + 1) % strip.getModeCount();
      colorUpdated(1);
    }

    if (digitalRead(BTN_NEXT_PALETTE) == LOW) {
      strip.setPalette(strip.getPaletteIndex() + 1);
      colorUpdated(1);
    }

    if (digitalRead(BTN_BRIGHTNESS) == LOW) {
      bri = (bri + 51) % 256; // step brightness (0–255 in steps of ~20%)
      colorUpdated(1);
    }

    // --- Joystick ---
    int joyX = analogRead(JOY_X);
    int joyY = analogRead(JOY_Y);

    // Map joystick X to effect index
    int effectIndex = map(joyX, 0, 4095, 0, strip.getModeCount()-1);
    effectCurrent = constrain(effectIndex, 0, strip.getModeCount()-1);

    // Map joystick Y to palette index
    int paletteIndex = map(joyY, 0, 4095, 0, strip.getPaletteCount()-1);
    strip.setPalette(constrain(paletteIndex, 0, strip.getPaletteCount()-1));

    colorUpdated(1); // push changes to WLED
  }

  uint16_t getId() { return 5678; } // unique ID
};

UsermodInput usermodInput;

#endif // USERMOD_INPUT

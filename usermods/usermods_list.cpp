/*
 * usermods_list.cpp
 * Defines which usermods are compiled into WLED.
 */

#include "wled.h"

// --- Custom Usermods ---
#include "usermod_st7789.cpp"   // LCD display
#include "usermod_input.cpp"    // Buttons + joystick

void registerUsermods() {
  // --- Register Usermods ---
  usermods.add(new UsermodST7789());   // LCD
  usermods.add(new UsermodInput());    // Input controls
}

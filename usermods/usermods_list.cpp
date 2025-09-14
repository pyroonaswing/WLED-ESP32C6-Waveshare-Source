/*
 * This file defines which usermods are compiled into WLED.
 * 
 * Add your custom usermods here.
 */

#include "wled.h"

// Example usermods (leave commented out unless you want them)
////# include "usermod_temperature.h"
////# include "usermod_audio.h"

// --- Your custom LCD usermod ---
#include "usermod_st7789.cpp"   // 👈 tells WLED about the LCD usermod

void registerUsermods() {
  // Example registrations
  ////usermods.add(new UsermodTemperature());
  ////usermods.add(new UsermodAudio());

  // --- Register your LCD usermod ---
  usermods.add(new UsermodST7789());   // 👈 actually enables it at runtime
}

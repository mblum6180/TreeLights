#include <FastLED.h>
#include "config.h"

CRGB leds[NUM_LEDS];
CRGB homeColors[NUM_HOMES]; // Array to store the color of each home
unsigned long previousMillis[NUM_HOMES]; // Store last time each home's LED was updated
long intervals[NUM_HOMES]; // Intervals at which each home blinks (milliseconds)
bool homeState[NUM_HOMES]; // Array to store the state (on/off) of each home
CRGB lastColor[NUM_HOMES]; // Array to store the last color of each home


void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // Define the color and initial interval for each home
  homeColors[0] = CRGB::Red; // First home color
  lastColor[0] = homeColors[0] // Initial last color
  intervals[0] = 500; // Initial interval for first home
  for (int i = 1; i < NUM_HOMES; i++) {
    homeColors[i] = CRGB::Green; // Other homes color
    lastColor[i] = homeColors[i];//  Initial last color
    intervals[i] = 42000 + 18000 * i; // Different initial interval for each home
  }

  memset(previousMillis, 0, sizeof(previousMillis)); // Initialize all previousMillis values to 0
  for (int i = 0; i < NUM_HOMES; i++) {
    homeState[i] = false; // Initialize all homes to be off
  }
}

void loop() {
  unsigned long currentMillis = millis();

  for (int home = 0; home < NUM_HOMES; home++) {
    if (currentMillis - previousMillis[home] >= intervals[home]) {
      previousMillis[home] = currentMillis;

      // Toggle the state of the home
      homeState[home] = !homeState[home];

      // Fade out if currently on, fade in if currently off
      if (homeState[home]) {
        // If turning on, fade in with the current color
        fadeLights(home, homeColors[home], true); // Fade in
      } else {
        // If turning off, first fade out, then change the color
        fadeLights(home, homeColors[home], false); // Fade out
        homeColors[home] = generateNewColor(home); // Assign a new color for next time
      }

      // Update the interval for this home based on its new state
      updateIntervalForHome(home, homeState[home]);
    }
  }
}


void updateIntervalForHome(int home, bool isCurrentlyOn) {
  long baseInterval, variation;

  if (isCurrentlyOn) {
    // Use the configurations from config.h
    baseInterval = ON_BASE_INTERVAL; // Base interval when lights are on
    variation = random(0, ON_VARIATION); // Variation interval when lights are on
  } else {
    // Use the configurations from config.h
    baseInterval = OFF_BASE_INTERVAL; // Base interval when lights are off
    variation = random(0, OFF_VARIATION); // Variation interval when lights are off
  }

  intervals[home] = baseInterval + variation; 
}


void fadeLights(int home, CRGB targetColor, bool fadeIn) {
  int ledStartIndex = (home == 0) ? 0 : 4 + 2 * (home - 1);
  int numLedsInHome = (home == 0) ? 4 : 2;
  int fadeSteps = 50; // Number of steps in the fade
  int fadeDelay = 12; // Milliseconds between fade steps

  for (int step = 0; step <= fadeSteps; step++) {
    float fadeFactor = fadeIn ? (float)step / fadeSteps : (float)(fadeSteps - step) / fadeSteps;

    for (int i = 0; i < numLedsInHome; i++) {
      leds[ledStartIndex + i] = targetColor;
      leds[ledStartIndex + i].nscale8(fadeFactor * 255);
    }

    FastLED.show();
    delay(fadeDelay);
  }
}


CRGB generateNewColor(int home) {
    const int christmasPaletteSize = sizeof(christmasPalette) / sizeof(christmasPalette[0]);

    CRGB newColor;
    do {
        newColor = christmasPalette[random(0, christmasPaletteSize)];
    } while(newColor == lastColor[home]);

    lastColor[home] = newColor; // Update the last color for this home
    return newColor;
}

#include <FastLED.h>

#define LED_PIN     6
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_HOMES   4 // Number of homes

#define NUM_LEDS    (4 + 2 * (NUM_HOMES - 1)) // Calculate number of LEDs

CRGB leds[NUM_LEDS];
CRGB homeColors[NUM_HOMES]; // Array to store the color of each home
unsigned long previousMillis[NUM_HOMES]; // Store last time each home's LED was updated
long intervals[NUM_HOMES]; // Intervals at which each home blinks (milliseconds)
bool homeState[NUM_HOMES]; // Array to store the state (on/off) of each home

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(1000);
  FastLED.clear();
  FastLED.show();

  // Define the color and initial interval for each home
  homeColors[0] = CRGB::Red; // First home color
  intervals[0] = 500; // Initial interval for first home
  for (int i = 1; i < NUM_HOMES; i++) {
    homeColors[i] = CRGB::Green; // Other homes color
    intervals[i] = 500 + 100 * i; // Different initial interval for each home
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
      bool newState = !homeState[home];

      // Fade out if currently on, fade in if currently off
      if (homeState[home]) {
        fadeLights(home, homeColors[home], false); // Fade out
      } else {
        fadeLights(home, homeColors[home], true); // Fade in
      }

      homeState[home] = newState;

      // Update the interval for this home based on its new state
      updateIntervalForHome(home, homeState[home]);
    }
  }
}


// Function to update the interval for a specific home
void updateIntervalForHome(int home, bool isCurrentlyOn) {


  if (isCurrentlyOn) {
    // If the lights are currently on, set a shorter interval for turning them off
    long baseInterval = 15 * 1000; // 15 minutes in milliseconds 60000 1000 for dubuging
    long variation = random(0, 30000); // Variation of up to 30 seconds
    intervals[home] = baseInterval + variation; 


  } else {
    // If the lights are currently off, set a longer interval for turning them on
    long baseInterval = 1 * 1000; // 15 minutes in milliseconds 60000 1000 for dubuging
    long variation = random(0, 1000); // Variation of up to 30 seconds
    intervals[home] = baseInterval + variation; 
  }
}

void fadeLights(int home, CRGB targetColor, bool fadeIn) {
  int ledStartIndex = (home == 0) ? 0 : 4 + 2 * (home - 1);
  int numLedsInHome = (home == 0) ? 4 : 2;
  int fadeSteps = 50; // Number of steps in the fade
  int fadeDelay = 10; // Milliseconds between fade steps

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

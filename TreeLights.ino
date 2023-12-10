#include <FastLED.h>

#define LED_PIN     6
#define LED_COUNT  14
#define HOME_COUNT 5

#define COLOR_ORDER GRB
#define CHIPSET     WS2812

CRGB leds[LED_COUNT];

unsigned long previousMillis[HOME_COUNT] = {0};
long onInterval[HOME_COUNT];
long offInterval[HOME_COUNT];
bool isFadingIn[HOME_COUNT] = {false};
CRGB homeColors[HOME_COUNT];
int brightness[HOME_COUNT] = {0};
int fadeAmount = 5;  // Amount by which the brightness changes

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
  FastLED.clear();
  FastLED.show();
  
  // Define colors for each home
  homeColors[0] = CRGB::Red;
  homeColors[1] = CRGB::Green;
  homeColors[2] = CRGB::Blue;
  homeColors[3] = CRGB::Yellow;
  homeColors[4] = CRGB(255, 105, 180); // Pink

  for(int i = 0; i < HOME_COUNT; i++) {
    onInterval[i] = random(300000, 900000);
    offInterval[i] = random(300000, 900000);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  for(int home = 0; home < HOME_COUNT; home++) {
    if(currentMillis - previousMillis[home] >= (isFadingIn[home] ? 30 : offInterval[home])) {
      toggleHomeLights(home);
      previousMillis[home] = currentMillis;
      if (!isFadingIn[home]) {
          offInterval[home] = random(300000, 900000); // Reset off interval for next cycle
      }
    }
    if (isFadingIn[home]) {
        fadeLights(home);
    }
  }
  FastLED.show();
}

void toggleHomeLights(int home) {
  int startLED = (home == 0) ? 0 : 4 + 2 * (home - 1);
  int ledCount = (home == 0) ? 4 : 2;

  if (!isFadingIn[home]) {
      brightness[home] = 0;
      isFadingIn[home] = true;
  } else {
      for(int i = startLED; i < startLED + ledCount; i++) {
          leds[i] = CRGB::Black; // Turn off lights
      }
      isFadingIn[home] = false;
  }
}

void fadeLights(int home) {
  int startLED = (home == 0) ? 0 : 4 + 2 * (home - 1);
  int ledCount = (home == 0) ? 4 : 2;
  
  brightness[home] += fadeAmount;
  if (brightness[home] <= 0 || brightness[home] >= 255) {
      fadeAmount = -fadeAmount;  // Reverse the direction of the fading at the ends
  }

  CRGB color = dimColor(homeColors[home], brightness[home]);
  for(int i = startLED; i < startLED + ledCount; i++) {
      leds[i] = color;
  }
}

CRGB dimColor(CRGB color, int brightness) {
  // Adjust brightness
  color.fadeToBlackBy(255 - brightness);
  return color;
}

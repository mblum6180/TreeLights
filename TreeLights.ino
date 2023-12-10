#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define LED_COUNT  14
#define HOME_COUNT 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis[HOME_COUNT] = {0};
long onInterval[HOME_COUNT];
long offInterval[HOME_COUNT];
bool isFadingIn[HOME_COUNT] = {false};
uint32_t homeColors[HOME_COUNT];
int brightness[HOME_COUNT] = {0};
int fadeAmount = 5;  // Amount by which the brightness changes

void setup() {
  strip.begin();
  strip.show();
  
  // Define colors for each home
  homeColors[0] = strip.Color(255, 0, 0); // Red
  homeColors[1] = strip.Color(0, 255, 0); // Green
  homeColors[2] = strip.Color(0, 0, 255); // Blue
  homeColors[3] = strip.Color(255, 255, 0); // Yellow
  homeColors[4] = strip.Color(255, 105, 180); // Pink

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
}

void toggleHomeLights(int home) {
  int startLED = (home == 0) ? 0 : 4 + 2 * (home - 1);
  int ledCount = (home == 0) ? 4 : 2;

  if (!isFadingIn[home]) {
      brightness[home] = 0;
      isFadingIn[home] = true;
  } else {
      for(int i = startLED; i < startLED + ledCount; i++) {
          strip.setPixelColor(i, strip.Color(0, 0, 0)); // Turn off lights
      }
      strip.show();
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

  uint32_t color = dimColor(homeColors[home], brightness[home]);
  for(int i = startLED; i < startLED + ledCount; i++) {
      strip.setPixelColor(i, color);
  }
  strip.show();
}

uint32_t dimColor(uint32_t color, int brightness) {
  // Extract color components
  uint8_t r = (uint8_t)(color >> 16);
  uint8_t g = (uint8_t)(color >> 8);
  uint8_t b = (uint8_t)color;
  
  // Adjust brightness
  r = (r * brightness) / 255;
  g = (g * brightness) / 255;
  b = (b * brightness) / 255;

  return strip.Color(r, g, b);
}

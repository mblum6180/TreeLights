// config.h

#ifndef CONFIG_H
#define CONFIG_H

#define LED_PIN     6
#define BRIGHTNESS  200
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_HOMES   4 // Number of homes
#define NUM_LEDS    (4 + 2 * (NUM_HOMES - 1)) // Calculate number of LEDs

// Intervals and variations for homes
#define ON_BASE_INTERVAL 10 * 60000  // Base interval when lights are on
#define OFF_BASE_INTERVAL 1 * 60000  // Base interval when lights are off
#define ON_VARIATION 20 * 60000      // Variation interval when lights are on
#define OFF_VARIATION 4 * 60000      // Variation interval when lights are off


// Define the color palette
const CRGB christmasPalette[] = {
    CRGB::Red,
    CRGB::Pink,
    CRGB::Green,
    CRGB::Purple,
    CRGB::Gold,
    CRGB::Orange,
    CRGB::Blue,
    CRGB::Cyan,
    CRGB::Aqua,
    CRGB::Lime,
    CRGB::Maroon,
    CRGB::Teal
};


#endif // CONFIG_H

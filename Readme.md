# Arduino LED Control Project

## Overview
This project controls a string of WS2812 LEDs (NeoPixels) using an Arduino. It's designed to create a dynamic light show for multiple "homes," each represented by a section of the LED strip. The project uses the FastLED library to manage color and brightness and includes features like fading effects and color changes.

## Features
- Control multiple sections of an LED strip, each representing a different "home."
- Dynamic fading effects for LEDs.
- Color changes after each fade-out cycle.
- Configurable settings for LED behavior.

## Hardware Requirements
- Arduino (Uno, Mega, etc.)
- WS2812 LED strip
- Power supply for LEDs

## Configuration
Adjustable settings are found in the `config.h` file, including:
- Number of homes (`NUM_HOMES`)
- LED pin (`LED_PIN`)
- Brightness level (`BRIGHTNESS`)

## Contributing
Contributions to this project are welcome. Please send pull requests or open issues for any enhancements, bug fixes, or improvements.

## License
MIT License

Copyright (c) Matthew Blum

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Author
Matthew Blum

## Acknowledgments
- FastLED library contributors



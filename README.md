# Glød - A Lo-Fi Scandinavian Mini Lamp

Glød is an interactive, Arduino-powered minimalist lamp built for CSE 493F (Physical Computing). It features multiple lighting modes driven by analog sensors, including a light-responsive nightlight and an adjustable ambient crossfading mode.

## Features

* **Mode 0 - Smart Nightlight:** Uses a photocell to read ambient light and adjusts the RGB LED brightness inversely (the darker the room, the brighter the crossfading colors become).
* **Mode 1 - Lo-Fi Ambient:** Uses a sliding potentiometer to manually control the brightness of the continuous RGB color crossfade.
* **Mode 2 - Reading Light:** Provides a static, warm soft-white light, with brightness fully adjustable via the slider.
* **Audio Feedback:** A piezo buzzer provides unique audio chimes to indicate exactly which mode has been selected when the user presses the button.

## Components

* Arduino Leonardo Microcontroller
* RGB LED (Common Cathode)
* Photocell (Photoresistor)
* Piezo Buzzer
* Tactile Push Button
* DIY Lo-Fi Rotary Potentiometer (Variable Resistor)
* Breadboard (Small) & Resistors
* Jumper Cables & Breadboarding Wires

**DIY Enclosure & Potentiometer Materials:**
* Cardboard & Origami Paper
* Paper Clip & Screw
* Rubber Bands & Electrical Tape
* Chopsticks & Pencil

## Credits & Acknowledgements

* **Author:** Jason Kim (Spring 2026)
* Hardware concepts, debouncing logic, and sensor integration were guided by the excellent [Interactive Physical Computing Textbook](https://makeabilitylab.github.io/physcomp/) by Dr. Jon Froehlich.
* Color conversion handled via the [RGBConverter Library](https://github.com/ratkins/RGBConverter).
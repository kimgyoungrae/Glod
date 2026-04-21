// Jason Kim
// CSE 493F - Physical Computing
// Spring 2026
// Glød - A Lo-Fi Scandinavian Mini Lamp

// Credit to Dr. Froehlich and the Interactive Physical Computing Textbook
// for information regarding crossfading RGB LEDs, using buttons, debouncing,
// photoresistors, potentiometers, using Piezo, and much much more:
// https://makeabilitylab.github.io/physcomp/

// Credit to the RGBConverter library outlined in the Physical Computing Textbook:
// https://github.com/ratkins/RGBConverter

#include "src/RGBConverter/RGBConverter.h"

// Pin Definitions
const int RGB_RED_PIN = 6;
const int RGB_GREEN_PIN = 5;
const int RGB_BLUE_PIN = 9;
const int BUTTON_PIN = 2; 
const int POT_PIN = A0; 
const int PHOTO_PIN = A1; 
const int PIEZO_PIN = 12; 

// Variables for Button Debouncing
int buttonState = LOW;             
int lastButtonState = LOW;         
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;  
const boolean COMMON_ANODE = false; 


// Modes or States:
// 0: Photoresistor RGB Crossfade (Brightness reacts inversely to room light)
// 1: Slider RGB Crossfade (Brightness controlled manually via slider)
// 2: Reading Light (Static soft white, brightness controlled via slider)
int currentMode = 0; 

float _hue = 0; // color position on color wheel (ranges from 0.0 to 1.0)
float _step = 0.001f; // crossfading speed
RGBConverter _rgbConverter;
int brightness = 255; 

void setup() {
  // Initialize RGB LED pins as output
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  // Initialize button as input
  pinMode(BUTTON_PIN, INPUT); 
  
  // Initialize Piezo buzzer as output
  pinMode(PIEZO_PIN, OUTPUT); 
  
  // Start serial communication
  Serial.begin(9600);   
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // If button state has changed due to bounce or press, reset timer.
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }

  // If state has been longer than the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Check to see if it's a new state
    if (reading != buttonState) {
      buttonState = reading; 

      // Trigger mode change when button goes LOW to HIGH (is pressed down)
      if (buttonState == HIGH) {
        
      
        currentMode++; 

        // Ensures that state transitions loop circularly
        if (currentMode > 2) {
          currentMode = 0; 
        }
        
        // Cycle through various modes (delay is so that chime plays the full duration):
        if (currentMode == 0) {
          tone(PIEZO_PIN, 1000, 100); delay(100);
          Serial.println("Mode Changed: Photoresistor RGB (Inversely Proportional)");
        } else if (currentMode == 1) {
          tone(PIEZO_PIN, 1500, 100); delay(100);
          Serial.println("Mode Changed: Slider RGB (Adjustable Crossfading)");
        } else if (currentMode == 2) {
          tone(PIEZO_PIN, 2000, 100); delay(100);
          Serial.println("Mode Changed: Reading Light (Soft White)");
        }
      }
    }
  }
  lastButtonState = reading; 

  if (currentMode == 0) {
    // Mode 0: Use Photoresistor
    int lightVal = analogRead(PHOTO_PIN);
    Serial.print("Photoresistor Raw: ");
    Serial.print(lightVal);
    // Maps inversely proportional as per spec
    brightness = map(lightVal, 200, 900, 255, 0); 
    Serial.print("  |  Mapped Brightness: ");
    Serial.println(brightness);
    
  } else {
    // Mode 1 and 2: Use Sliding Potentiometer (Variable Resistor)
    int potVal = analogRead(POT_PIN);
    Serial.print("Slider Raw: ");
    Serial.print(potVal);

    // Map proportionally for sliding pot.
    brightness = map(potVal, 200, 850, 0, 255);
    Serial.print("  |  Mapped Brightness: ");
    Serial.println(brightness);
  }
  
  // Limit the range of brightness from 0 to 255.
  brightness = constrain(brightness, 0, 255);

  if (currentMode == 2) {
    // Mode 2: Static Soft White
    setColor(255, 214, 170); 
    
  } else {
    // Mode 0 and 1: Crossfading Colors
    byte rgb[3]; // Holds the RGB values.

    // Converts HSL to RGB, applies the calculated colors, increments hue shift, and resets.

    _rgbConverter.hslToRgb(_hue, 1, 0.5, rgb);
    setColor(rgb[0], rgb[1], rgb[2]); 
    
    _hue += _step;
    if(_hue > 1.0) { _hue = 0; }

  }
    
  // Delay is to make sure readings are stable.
  delay(10); 
}

// Adapted from Dr. Froehlich's code.
void setColor(int red, int green, int blue) {
  if(COMMON_ANODE == true){
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  }
  

  // Similar as before, but scale raw color values by current brightness 
  // percentage and divide by 255 to adapt brightness.
  int finalRed = ((long)red * brightness) / 255;
  int finalGreen = ((long)green * brightness) / 255;
  int finalBlue = ((long)blue * brightness) / 255;

  analogWrite(RGB_RED_PIN, finalRed);
  analogWrite(RGB_GREEN_PIN, finalGreen);
  analogWrite(RGB_BLUE_PIN, finalBlue);
}
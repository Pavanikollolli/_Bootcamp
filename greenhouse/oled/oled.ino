#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
 
  Serial.begin(9600);


  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer (removes the default Adafruit splash screen)
  display.clearDisplay();

  // Set text size (1 is small, 2 is medium, etc.)
  display.setTextSize(1);      
  
  // Set text color (WHITE means pixel on for monochrome screens)
  display.setTextColor(SSD1306_WHITE);  
  
  // Set cursor position (x, y) coordinates
  display.setCursor(0, 10);     
  
  // Print your message
  display.println("Hello");

  // Pushes the text buffer from Arduino memory to the actual screen hardware
  display.display(); 
}

void loop() {
  // Nothing needed here for static text
}


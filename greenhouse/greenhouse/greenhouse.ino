/*
  Greenhouse Monitor — simplified, using Adafruit GFX/SSD1306 for the OLED
  DHT22 -> D2 | Light -> A0 | Soil -> A1 | IR -> D3
  OLED -> A4/A5 (I2C) | Buzzer -> D4 | Water LED -> D5 | Vent LED -> D6

  Libraries needed: DHT sensor library, Adafruit Unified Sensor,
  Adafruit GFX Library, Adafruit SSD1306 (use SH110X instead if your
  1.3" OLED shows nothing/garbage — most 1.3" 128x64 panels are
  actually SH1106, not SSD1306).

  DISPLAY SIZE NOTE: the physical screen is a fixed 128x64 pixels, so
  "bigger display" means bigger TEXT, done here with setTextSize()
  instead of a different font file. Size 2 text can't fit everything
  on one screen at once, so the code alternates between two screens
  (status/temp/humidity, then soil/vent/water) every loop cycle.
*/

#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN 2
#define LIGHT_PIN A0
#define SOIL_PIN A1
#define IR_PIN 3
#define BUZZER_PIN 4
#define WATER_LED_PIN 5
#define VENT_LED_PIN 6

// Calibrate these two for your soil sensor (dry vs. in water)
#define SOIL_DRY 1023
#define SOIL_WET 320

DHT dht(DHT_PIN, DHT22);
Adafruit_SSD1306 display(128, 64, &Wire, -1);

bool showFirstScreen = true; // toggles which screen is drawn each cycle

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(WATER_LED_PIN, OUTPUT);
  pinMode(VENT_LED_PIN, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  delay(2000); // let the DHT22 warm up
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int soilPct = map(analogRead(SOIL_PIN), SOIL_DRY, SOIL_WET, 0, 100);
  bool hot = temp > 28 || (digitalRead(IR_PIN) == HIGH && temp > 24); // IR confirms borderline heat
  bool dry = soilPct < 30;
  bool alert = temp > 34 || hum < 25 || hum > 85 || soilPct < 15;

  // Ventilation LED: on when hot, blinking if critically hot
  digitalWrite(VENT_LED_PIN, temp > 34 ? (millis() / 250) % 2 : hot);
  // Water warning LED
  digitalWrite(WATER_LED_PIN, dry);
  // Buzzer for serious problems
  digitalWrite(BUZZER_PIN, alert);

  String status = alert ? "ALERT" : (hot || dry) ? "WATCH" : "GOOD";
  String ventState = hot ? "OPEN" : "CLOSED";

  Serial.println("Status: " + status);
  Serial.println("Temp: " + String(temp) + "C  Hum: " + String(hum) + "%");
  Serial.println("Soil: " + String(soilPct) + "%  Vent: " + ventState);

  // Size 2 text for the headline, size 1 for the two readings underneath.
  display.clearDisplay();
  if (showFirstScreen) {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println(status);
    display.setTextSize(1);
    display.setCursor(0, 24);
    display.println("Temp " + String(temp) + "C");
    display.setCursor(0, 40);
    display.println("Hum  " + String(hum) + "%");
  } else {
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Soil " + String(soilPct) + "%");
    display.setTextSize(1);
    display.setCursor(0, 24);
    display.println("Vent " + ventState);
    if (dry) {
      display.setCursor(0, 40);
      display.println("WATER NOW");
    }
  }
  display.display();

  showFirstScreen = !showFirstScreen; // flip to the other screen next cycle
  delay(4000);
}

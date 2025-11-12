#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_SHT31.h>
#include <Wire.h>
#include <SPI.h>

// -------------------- Pin Definitions --------------------
#define TFT_CS   10
#define TFT_RST  8
#define TFT_DC   9

#define RELAY2   7
#define TRANSISTOR_PIN 6   // humidity control
#define LED_STRIP_PIN 3    // Transistor for LED strip
#define TOGGLE_SWITCH 12   // Switch input pin

// -------------------- Objects --------------------
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// -------------------- Timing Variables --------------------
unsigned long lastLEDToggle = 0;
bool ledState = false;
bool lastSwitchState = HIGH; 

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Booting...");

  // Initialize TFT display 
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(0); // Portrait
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 5);
  tft.println("Environment Monitor");

  pinMode(RELAY2, OUTPUT);
  pinMode(TRANSISTOR_PIN, OUTPUT);
  pinMode(LED_STRIP_PIN, OUTPUT);
  pinMode(TOGGLE_SWITCH, INPUT_PULLUP); 

  // Default outputs 
  digitalWrite(RELAY2, HIGH);
  digitalWrite(TRANSISTOR_PIN, HIGH);
  digitalWrite(LED_STRIP_PIN, LOW); // Start LED off

  // Initialize SHT31
  if (!sht31.begin(0x44)) {
    Serial.println("Couldn't find SHT31 sensor!");
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(10, 20);
    tft.println("SHT31 not found!");
  } else {
    Serial.println("SHT31 connected.");
    tft.setCursor(10, 20);
    tft.setTextColor(ST77XX_GREEN);
    tft.println("SHT31 OK");
  }

  delay(2000);
}

// -------------------- Loop --------------------
void loop() {
  float h = sht31.readHumidity();
  float t = sht31.readTemperature() * 9 / 5 + 32; // Convert °C to °F

  // --- Read Toggle Switch ---
  bool switchState = digitalRead(TOGGLE_SWITCH) == LOW;

  // --- Detect switch change ---
  if (switchState && !lastSwitchState) {
    ledState = true;
    digitalWrite(LED_STRIP_PIN, HIGH);
    lastLEDToggle = millis();
  }

  // --- LED Strip Logic ---
  if (switchState) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastLEDToggle >= 43200000) { // 12 hours
      ledState = !ledState; // Toggle LED state
      digitalWrite(LED_STRIP_PIN, ledState ? HIGH : LOW);
      lastLEDToggle = currentMillis;
    }
  } else {
    // Switch is OFF → ensure LED is OFF
    ledState = false;
    digitalWrite(LED_STRIP_PIN, LOW);
  }

  // Remember the last switch state
  lastSwitchState = switchState;

  // --- Error Handling ---
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from SHT31 sensor!");

    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(10, 60);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(2);
    tft.println("Sensor Error");

    delay(2000);
    return;
  }

  // --- Debug Output ---
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %  ");
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print(" *F  |  Switch: ");
  Serial.print(switchState ? "ON" : "OFF");
  Serial.print("  |  LED: ");
  Serial.println(ledState ? "ON" : "OFF");

  // --- Relay + Transistor Control ---
  if (h < 85) {
    digitalWrite(RELAY2, LOW); // ON when humidity < 85%
    digitalWrite(TRANSISTOR_PIN, HIGH); // ON when humidity < 85%
  } else {
    digitalWrite(RELAY2, HIGH); // OFF when humidity >= 85%
    digitalWrite(TRANSISTOR_PIN, LOW); // OFF when humidity >= 85%
  }

  // --- Update TFT Display ---
  tft.fillRect(0, 20, 128, 140, ST77XX_BLACK);

  // Humidity
  tft.setCursor(16, 20);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print("Humidity");

  tft.setCursor(20, 40);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(3);
  tft.print(h, 1);
  tft.print("%");

  // Temperature
  tft.setCursor(40, 65);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print("Temp");

  tft.setCursor(10, 85);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(3);
  tft.print(t, 1);
  tft.print(" F");

  // Switch + LED status
  tft.setCursor(35, 115);
  tft.setTextSize(1);
  tft.setTextColor(switchState ? ST77XX_GREEN : ST77XX_YELLOW);
  tft.print("Switch: ");
  tft.println(switchState ? "ON" : "OFF");

  tft.setCursor(42, 125);
  tft.setTextColor(ledState ? ST77XX_GREEN : ST77XX_YELLOW);
  tft.print("LED: ");
  tft.println(ledState ? "ON" : "OFF");

  delay(500); 
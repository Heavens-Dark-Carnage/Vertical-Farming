#define BLYNK_TEMPLATE_ID "TMPL6NnNR98c7"
#define BLYNK_TEMPLATE_NAME "Vertical Farming"
#define BLYNK_AUTH_TOKEN "LqERa4MCW-rF7VJCD_LchGg8MUroBmwp"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "Westford Student"; // Replace with your WiFi SSID
char pass[] = "justgoahead"; // Replace with your WiFi password

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin Definitions
#define DHTPIN 4          // Pin connected to DHT11
#define DHTTYPE DHT11     // Using DHT11
#define LDR_PIN 34        // Pin connected to LDR
#define SOIL_PIN 35       // Pin connected to Soil Moisture Sensor
#define WATER_PIN 32      // Pin connected to Water Sensor
#define LED_PIN 15        // Pin connected to LED
#define PUMP_PIN 14       // Pin connected to Water Pump

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Thresholds for LED alert
#define MOISTURE_THRESHOLD 500  // Adjust based on testing
#define LIGHT_THRESHOLD 2000    // Adjust based on testing
#define WATER_THRESHOLD 500     // Adjust based on testing

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();

  // Initialize DHT sensor
  dht.begin();

  // Initialize LED and Pump pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);
}

void loop() {
  Blynk.run(); // Run Blynk

  // Read DHT11 Sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read LDR (Light level)
  int lightLevel = analogRead(LDR_PIN);

  // Read Soil Moisture Sensor
  int soilMoisture = analogRead(SOIL_PIN);

  // Read Water Sensor
  int waterLevel = analogRead(WATER_PIN);

  // Send sensor data to Blynk
  Blynk.virtualWrite(V0, temperature);  // Temperature
  Blynk.virtualWrite(V1, humidity);     // Humidity
  Blynk.virtualWrite(V2, lightLevel);   // Light Level
  Blynk.virtualWrite(V3, soilMoisture); // Soil Moisture
  Blynk.virtualWrite(V4, waterLevel);   // Water Level

  // Display data on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Temperature and Humidity
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  // Light Level
  display.print("Light: ");
  display.print(lightLevel);
  display.println();

  // Soil Moisture Level
  display.print("Soil Moisture: ");
  display.print(soilMoisture);
  display.println();

  // Water Level
  display.print("Water Level: ");
  display.print(waterLevel > WATER_THRESHOLD ? "High" : "Low");

  // LED and Pump Control based on thresholds
  if (waterLevel < WATER_THRESHOLD) {
    // Water level is low: Turn on pump and blink LED
    digitalWrite(PUMP_PIN, LOW); // Turn on pump
    digitalWrite(LED_PIN, millis() % 500 < 250 ? HIGH : LOW); // Blink LED every 250ms
  } else {
    // Water level is high: Turn off pump and keep LED on
    digitalWrite(PUMP_PIN, HIGH); // Turn off pump
    digitalWrite(LED_PIN, HIGH); // Turn on LED solid
  }

  display.display();  // Display all updates
  delay(2000);        // Update every 2 seconds
}

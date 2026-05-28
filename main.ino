#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>

// Screen Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor Configuration
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp;

// Timing Variables (Non-blocking timers)
unsigned long lastSensorRead = 0;
unsigned long lastApiFetch = 0;
const unsigned long sensorInterval = 2000;      // 2 seconds
const unsigned long apiInterval = 900000;       // 15 minutes

// Network Credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
String apiKey = "YOUR_OPENWEATHERMAP_API_KEY";
String city = "London"; 

void setup() {
  Serial.begin(115200);
  
  // Initialize Screen
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Booting up...");
  display.display();

  // Initialize Sensors
  dht.begin();
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
}

void loop() {
  unsigned long currentMillis = millis();

  // Task 1: Read local data every 2 seconds
  if (currentMillis - lastSensorRead >= sensorInterval) {
    lastSensorRead = currentMillis;
    
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    float pres = bmp.readPressure() / 100.0F; // Pa to hPa
    
    // Print to Serial for debugging
    Serial.print("Temp: "); Serial.print(temp);
    Serial.print(" | Hum: "); Serial.print(hum);
    Serial.print(" | Pres: "); Serial.println(pres);
    
    // Update local UI screen
    display.clearDisplay();
    display.setCursor(0,0);
    display.printf("Indoor Temp: %.1f C\n", temp);
    display.printf("Humidity: %.1f%%\n", hum);
    display.printf("Pressure: %.1f hPa\n", pres);
    display.display();
  }

  // Task 2: Fetch Cloud Data every 15 minutes
  if (currentMillis - lastApiFetch >= apiInterval) {
    lastApiFetch = currentMillis;
    
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
      
      http.begin(serverPath);
      int httpResponseCode = http.GET();
      
      if (httpResponseCode > 0) {
        String payload = http.getString();
        StaticJsonDocument<1024> doc;
        deserializeJson(doc, payload);
        
        float outdoorTemp = doc["main"]["temp"];
        const char* weatherDesc = doc["weather"][0]["description"];
        
        Serial.print("Outdoor Temp: "); Serial.println(outdoorTemp);
        Serial.print("Condition: "); Serial.println(weatherDesc);
      }
      http.end();
    }
  }
}

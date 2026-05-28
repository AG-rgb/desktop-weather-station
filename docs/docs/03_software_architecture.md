# Software Architecture & Firmware Logic

This document details the firmware structure, required development libraries, and execution blocks for the ESP32 Desktop Weather Station. The firmware is written using the Arduino framework.

---

## 1. Required Libraries & Modules
To interface with the hardware and handle Wi-Fi data, the project relies on the following open-source frameworks:
* `WiFi.h` - Native ESP32 library to handle network connections.
* `HTTPClient.h` & `ArduinoJson.h` - To send GET requests to weather APIs and parse JSON payloads.
* `Adafruit_SSD1306.h` & `Adafruit_GFX.h` - For driving the I2C OLED display screen graphics.
* `DHT.h` - For reading digital temperature and humidity data from the DHT22.
* `Adafruit_BMP280.h` - For handling the I2C communication with the barometric pressure sensor.

---

## 2. Firmware Initialization (void setup())
When the device boots up, it executes the configuration block exactly once:

```cpp
void setup() {
  // 1. Initialize hardware Serial monitor for debugging at 115200 baud
  Serial.begin(115200);
  
  // 2. Initialize I2C Bus and check for peripheral sensor attachments
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("OLED allocation failed");
  }
  dht.begin();
  bmp.begin(0x76);
  
  // 3. Connect to local Wi-Fi Network
  WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Display loading animation on screen
  }
}


void loop() {
  unsigned long currentMillis = millis();

  // Task 1: Read local sensors every 2 seconds
  if (currentMillis - lastSensorRead >= 2000) {
    lastSensorRead = currentMillis;
    
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    float pres = bmp.readPressure() / 100.0F; // Convert Pa to hPa
    
    updateDisplayLocal(temp, hum, pres);
  }

  // Task 2: Fetch cloud weather data every 15 minutes
  if (currentMillis - lastApiFetch >= 900000) {
    lastApiFetch = currentMillis;
    
    if (WiFi.status() == WL_CONNECTED) {
      fetchOutdoorWeather();
    }
  }
}

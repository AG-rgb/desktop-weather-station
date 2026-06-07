Desktop Weather Station
A compact ESP32‑powered desktop weather station built with a custom Onshape‑designed enclosure for Hack Club Fallout. It monitors indoor conditions in real time and pulls outdoor weather data over Wi‑Fi using API requests.

1. Project Overview
Microcontroller: ESP32‑WROOM‑32D

Display: 0.96" I2C OLED Screen

Sensors: DHT22 (Temperature/Humidity) & BMP280 (Barometric Pressure)



2. Bill of Materials (BOM)
ESP32‑WROOM‑32D Development Board (Qty: 1) – Serves as the main microcontroller and handles all Wi‑Fi communication. Cost: $5.00

0.96" I2C OLED Display Module (Qty: 1) – Small screen used to show live weather data and system info. Cost: $4.00

DHT22 Temperature & Humidity Sensor (Qty: 1) – Measures indoor temperature and humidity levels. Cost: $4.00

BMP280 Barometric Pressure Sensor (Qty: 1) – Tracks atmospheric pressure for weather trend insights. Cost: $3.00

Jumper Wires & Breadboard/Perfboard (Qty: 1) – Used for wiring and assembling the internal electronics. Cost: $5.00

PLA 3D Printing Filament (Qty: 1) – Material for printing the enclosure and lid. Cost: $10.00

Total Estimated Budget: $31.00



4. Software Logic & Data Flow
The firmware is structured to multitask cleanly so the display stays responsive while background processes handle sensor reads and API calls:

Startup Sequence — When the device powers on, it initializes the I²C bus, OLED display, and both sensors. After that, it attempts to connect to Wi‑Fi and shows the connection status on the screen.

Local Sensor Loop (Every 2 seconds) — Continuously reads temperature and humidity from the DHT22, along with barometric pressure from the BMP280. These values update on the display in real time so the indoor data always feels live.

API Weather Loop (Every 15 minutes) — Uses Wi‑Fi to reach the OpenWeatherMap API, pulls the latest outdoor conditions, and refreshes the background or secondary display elements with the new forecast.

3. Mechanical & Enclosure Notes
The enclosure was modeled in Onshape with a focus on clean airflow, sensor accuracy, and secure internal mounting:

Internal Standoffs — The base includes built‑in M2 standoffs that let the ESP32 and sensor boards mount firmly without wobble or stress on the wiring.

Thermal Separation — Since the ESP32 generates heat, the DHT22 is placed in its own isolated chamber behind the front vents. This prevents warm air from the microcontroller from skewing temperature and humidity readings.



<img width="1410" height="2000" alt="Untitled design" src="https://github.com/user-attachments/assets/20dbec0b-b0d5-45cb-854d-9de9401c5482" />


README explains what the project is
Project Chimney is an ESP32‑powered environmental monitoring station built to avoid the heat problems that plague typical 3D‑printed enclosures. It continuously reads temperature, humidity, and pressure data, then streams everything to a live web dashboard.
README explains why it was made
Most small enclosures trap the heat produced by the microcontroller, which throws off temperature readings by 2–3°C. Project Chimney fixes that by using a passive convection chimney—essentially a built‑in stack effect—to pull fresh ambient air across the sensors. This keeps the readings accurate and reflective of real conditions.

README explains how to use/build it
1. Clone the repository onto your computer.
2. Open the firmware in the Arduino IDE, install the ESP32 board package, and upload it to your ESP32 DevKit.
3. Connect the DHT22, BMP280, and OLED display to the ESP32 following the documented wiring.
4. Open the CodePen dashboard to view your live telemetry stream.



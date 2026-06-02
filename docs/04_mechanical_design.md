Mechanical Design & Enclosure Architecture
This section breaks down how the enclosure is shaped, how each omponent is mounted, and how the internal layout manages heat. All modeling and fit checks were done in Onshape.

Physical Dimensions and Form Factor
The enclosure uses a simple, compact rectangular shape that prints cleanly and sits neatly on a desk.
Footprint: a small rectangular housing with flat faces, optimized for stable 3D-printing orientation and a clean desktop profile.
Wall thickness: a consistent 2.0 mm shell across all sides, providing enough rigidity while keeping filament use efficient.
Material Selection - PETG or PLA, with PLA chosen for its reliable dimensional accuracy and ease of printing - ideal for an indoor device that won't face temperature extremes.

Internal Component Mounting and Standoffs
To avoid shorts and keep wiring tidy, the enclosure includes built-in mounting features molded directly into the interior.
ESP32 Node MCU Board - Supported on integrated standoffs or channels that lift the board off the walls and leave room underneath for wire routing.
0.96/" OLED Screen - Positioned flush behind the front window using corner alignment stops, then secured with adhesive or a small clip style retainer.
Sensor Brackets: Low-profile tabs or blocks on the internal floor hold the DHT22 and BMP280 modules in place using a simple friction-fit.

Thermal Management and Airflow Optimization
Because the ESP32 produces noticeable heat during Wi-Fi activity, the enclosure layout separates components so the sensors stay in a cooler, more stable air pocket. This prevents the microcontroller's heat from drifting into the sensing area and keeps temperature and humidity readings accurate.

Spatial Separation: the internal layout places the ESP32 and the sensor modules on opposite sides of the enclosure so the DHt22 and BMP280 stay clear of the ESP32's heat plume. This keeps the sensing chamber thermally stable and prevents warm air from drifting into the measurement zone. 
Passive Ventilation Slots: slim perimeter vents are built into the enclsoure walls to let ambient room air flow naturally across the sensors. This passive airflow helps the device track real time indoor conditions without requiring any active cooling.
Port Access: a cleanr ectangular opening on the exterior wall provides direct access to the ESP32's Micro-USB or USB-C port. The cutout is sized so the cable seats flush without bending or stressing the connector.


Final Protoype Iteration: Top Ventilation Grid
The final CAD version replaced the solid top panel with a lightweight, 3 row by 10 column ventilation grid to improve airflow and overall thermal performance.
Manufacturing Execution: The grid was created using an Onshape feature pattern, replicating a single custom slot across both the horizontal and vertical axes of the top surface. This keeps the geometry consistent and ensures the mesh prints cleanly.
Structural Integrity: A minimum 10 mm plastic wall thickness was preserved between each slot. This spacing prevents sagging during printing, maintains strong toolpaths, and avoids filament drooping across the openings.
Thermal Teesting Blueprint: The optimized mesh significantly improves passive heat dissipation from the ESP32-s Wi-Fi module. By venting warm air upward, the lower sensor chamber stays thermally stable and maintains accurate environmental readings.

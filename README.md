# Smart Plant Monitoring & Watering System (Arduino)

An embedded system that monitors soil moisture and environmental conditions and automatically waters a plant using a relay-controlled pump.

## Features
- Arduino Uno + DHT11 + capacitive soil sensor + relay + submersible pump
- Control algorithms with calibrated thresholds, hysteresis, min/max run time, and cooldown
- Serial output for live readings and calibration

## Hardware
- Arduino Uno 
- DHT11 
- Capacitive soil moisture sensor 
- 1-channel relay module 
- 5V submersible pump + tubing
- Separate pump power source 
- Breadboard, jumpers

See **docs/wiring.md** for connections and safety notes.

## Quick Start
1. Install Arduino IDE and libraries:
   - **Adafruit DHT sensor library**
   - **Adafruit Unified Sensor**
2. Open `src/SmartPlantMonitor.ino` and upload to the board.
3. Open **Serial Monitor** at **9600 baud** to view readings.

## Calibration
1. Note the **soil** value in dry soil/air; set `DRY_ON_THRESHOLD` slightly below that.
2. Wet the probe/soil; note the value; set `WET_OFF_THRESHOLD` slightly above that.
3. Keep a **50–100** gap between the two to prevent relay chatter.

## Repo Contents
- `src/SmartPlantMonitor.ino` – main firmware
- `wiring.md` – wiring map and relay/pump connection guide
- `materials.md` – parts list with notes
- `docs/images/` – add your wiring photo and demo screenshot

## Demo
_Add a short GIF or image here after testing._

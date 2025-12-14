# Smart Plant Monitoring & Watering System (Arduino)


## Overview
- The purpose of this project is to implement an embedded, sensor driven automated watering system designed to replace manual or fixed schedule plant watering. The system continuously monitors soil moisture and environmental conditions and uses control logic to actuate a relay driven water pump only when watering is required. By responding to real time sensor data rather than a fixed daily schedule, the system improves efficiency and demonstrates closed loop control and automation concepts commonly used in embedded and industrial systems.

## Main Issues
- I ran into a few issues with some of the hardware and the wiring to where I didnt have a specific adapter to actually wire and give power to my pump so my work around was cutting off the adapter that was on the componet, which was a barrel head port and manually wired the battery that way. This way I didn't have to spend money to get a whole connector to give power to my device. Another problem I ran into was the code I had problems with timing behavior I had problems with rapid switching so adding the fixed delay allowed me to prevent it from switching rapidly.

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

## Project Images
- Image 1 shows a brief overview of how I started my wiring process and some of the componets used
- Image 2 shows the final wiring along with how I have the pump set up in water going all the way to a cup of soil


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
- `images.md` – add your wiring photo and demo screenshot



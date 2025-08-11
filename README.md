# Smart-Plant-Monitoring-and-Watering-System-Arduino-
ng System (Arduino)

An embedded system that monitors soil moisture and environmental conditions and automatically waters a plant using a relay-controlled pump.

## Features
- Arduino Uno + DHT11 + capacitive soil sensor + relay + submersible pump
- Control algorithms with calibrated thresholds, hysteresis, min/max run time, and cooldown
- Serial output for live readings and calibration

## Hardware
- Arduino Uno (or Nano)
- DHT11 (3-pin module)
- Capacitive soil moisture sensor (analog)
- 1-channel relay module (DC+, DC-, IN; COM/NO/NC terminals)
- 5V submersible pump + tubing
- Separate pump power source (e.g., 5V/1–2A adapter or battery pack)
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
- `docs/wiring.md` – wiring map and relay/pump connection guide
- `hardware/bill_of_materials.md` – parts list with notes
- `docs/images/` – add your wiring photo and demo screenshot

## Demo
_Add a short GIF or image here after testing._

## License
MIT — see `LICENSE`.
src/SmartPlantMonitor.ino
cpp
Copy
Edit
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const int SOIL_PIN = A0;
const int RELAY_PIN = 4;

DHT dht(DHTPIN, DHTTYPE);

int DRY_ON_THRESHOLD  = 700;
int WET_OFF_THRESHOLD = 650;

unsigned long MIN_RUN_MS  = 3000;
unsigned long MAX_RUN_MS  = 15000;
unsigned long COOLDOWN_MS = 20000;
unsigned long SAMPLE_MS   = 1000;

bool pumpOn = false;
unsigned long lastChangeMs = 0;
unsigned long lastSampleMs = 0;

void setPump(bool on) {
  pumpOn = on;
  lastChangeMs = millis();
  digitalWrite(RELAY_PIN, on ? LOW : HIGH);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  delay(1500);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleMs >= SAMPLE_MS) {
    lastSampleMs = now;

    int soil = analogRead(SOIL_PIN);
    float tC = dht.readTemperature();
    float h  = dht.readHumidity();

    Serial.print("Soil: "); Serial.print(soil);
    Serial.print(" | Temp: "); Serial.print(isnan(tC) ? -999 : tC); Serial.print(" C");
    Serial.print(" | Humidity: "); Serial.print(isnan(h) ? -999 : h); Serial.println(" %");

    if (!pumpOn) {
      bool cooldownOver = (now - lastChangeMs >= COOLDOWN_MS);
      if (cooldownOver && soil >= DRY_ON_THRESHOLD) setPump(true);
    } else {
      unsigned long runMs = now - lastChangeMs;
      bool reachedMax = runMs >= MAX_RUN_MS;
      bool minSatisfied = runMs >= MIN_RUN_MS;
      bool soilWetEnough = soil <= WET_OFF_THRESHOLD;
      if (reachedMax || (minSatisfied && soilWetEnough)) setPump(false);
    }
  }
}
docs/wiring.md
markdown
Copy
Edit
# Wiring Guide

## Sensors → Arduino
**DHT11 (3-pin module)**  
- VCC → 5V  
- DATA → D2  
- GND → GND

**Capacitive soil sensor**  
- VCC → 5V  
- AOUT → A0  
- GND → GND

## Relay (signal header)
- DC+ → 5V  
- DC- → GND  
- IN  → D4

## Relay (screw terminals)
- COM → + from pump power supply  
- NO  → + to pump  
- NC  → not used

## Pump & Power
- Pump − → − of pump power supply  
- Tie pump power supply − to Arduino **GND** (common ground)

**Important:** Only the **positive** line to the pump goes through the relay (COM→NO). The negative line goes directly to the power supply negative and common ground with Arduino.

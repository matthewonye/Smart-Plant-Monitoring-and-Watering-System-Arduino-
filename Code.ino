#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const int SOIL_SENSOR_PIN = A0;
const int RELAY_PIN = 4;

int moistureThreshold = 500;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // relay OFF

  dht.begin();

  Serial.println("Smart Plant Monitoring System Initialized");
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Soil: ");
  Serial.print(soilValue);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.println(humidity);

  if (soilValue > moistureThreshold) {
    digitalWrite(RELAY_PIN, LOW); // pump ON
    Serial.println("Pump ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // pump OFF
    Serial.println("Pump OFF");
  }

  delay(2000);
}


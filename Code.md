const int RELAY_PIN = 4; // Relay signal pin

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Keep relay OFF at startup
}

void loop() {
  digitalWrite(RELAY_PIN, LOW);  // Turn relay ON (pump runs)
  delay(3000);                   // Run for 3 seconds
  digitalWrite(RELAY_PIN, HIGH); // Turn relay OFF (pump stops)
  delay(3000);                   // Wait 3 seconds
}


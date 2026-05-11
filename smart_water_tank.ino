// Smart Water Tank System (ESP32)

#define TRIG_PIN 5
#define ECHO_PIN 18
#define RELAY_PIN 23   // controls LED / pump simulator

// Adjust this based on your tank height (in cm)
float tankHeight = 100.0;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // pump OFF initially
}

void loop() {

  // STEP 1: Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // STEP 2: Read echo time
  long duration = pulseIn(ECHO_PIN, HIGH);

  // STEP 3: Convert to distance (cm)
  float distance = duration * 0.034 / 2;

  // STEP 4: Calculate water level
  float waterLevel = tankHeight - distance;

  // Convert to percentage
  float waterPercent = (waterLevel / tankHeight) * 100;

  Serial.print("Water Level: ");
  Serial.print(waterPercent);
  Serial.println(" %");

  // STEP 5: CONTROL LOGIC

  if (waterPercent < 30) {
    // LOW WATER → turn ON pump (LED ON)
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Pump ON (Filling tank)");
  }
  else if (waterPercent > 80) {
    // FULL WATER → turn OFF pump
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Pump OFF (Tank full)");
  }

  delay(2000);
}

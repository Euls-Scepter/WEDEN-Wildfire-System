#include <ESP32Servo.h>

// Pin Definitions
#define MQ2_PIN 34
#define TEMP_PIN 35
#define BUZZER_PIN 25
#define SERVO_PIN 13
#define LED_GREEN_PIN 12
#define LED_RED_PIN 14

// Thresholds
const int SMOKE_THRESHOLD = 2000;  // Threshold for MQ-2 / Gas Sensor
const int TEMP_THRESHOLD = 1500;   // Threshold for Temp Sensor

Servo gateServo;

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_PIN, INPUT);
  pinMode(TEMP_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);

  gateServo.attach(SERVO_PIN);
  gateServo.write(0); // Gate Closed by default

  // Normal State Init
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("WEDEN System Online & Monitoring...");
}

void loop() {
  int rawGas = analogRead(MQ2_PIN);
  int rawTemp = analogRead(TEMP_PIN);

  Serial.print("Gas Reading: ");
  Serial.print(rawGas);
  Serial.print(" | Temp Reading: ");
  Serial.println(rawTemp);

  // Local Fail-Safe Action
  if (rawGas > SMOKE_THRESHOLD || rawTemp > TEMP_THRESHOLD) {
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, HIGH);
    tone(BUZZER_PIN, 500);
    gateServo.write(90); // Open evacuation gate
    Serial.println("!! EMERGENCY: Wildfire Threat Detected! Evacuation Gate Opened !!");
  } else {
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, LOW);
    noTone(BUZZER_PIN);
    gateServo.write(0);  // Keep gate closed
  }

  delay(1000);
}

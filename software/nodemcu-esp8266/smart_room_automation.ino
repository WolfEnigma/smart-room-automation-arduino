#include <DHT.h>

/* -------- Pin Definitions -------- */
#define DHTPIN D4
#define DHTTYPE DHT11

#define LDR_PIN A0
#define SMOKE_PIN D1
#define RAIN_PIN D2

#define FAN_RELAY D5
#define LIGHT_RELAY D6
#define BUZZER D7

/* -------- Objects -------- */
DHT dht(DHTPIN, DHTTYPE);

/* -------- Thresholds -------- */
int tempThreshold = 30;   // Celsius
int lightThreshold = 500;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LDR_PIN, INPUT);
  pinMode(SMOKE_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);

  pinMode(FAN_RELAY, OUTPUT);
  pinMode(LIGHT_RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(FAN_RELAY, LOW);
  digitalWrite(LIGHT_RELAY, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("Smart Room System Initialized");
}

void loop() {
  temperatureControl();
  lightingControl();
  smokeDetection();
  rainDetection();

  delay(2000);
}

/* -------- Temperature-Based Fan Control -------- */
void temperatureControl() {
  float temperature = dht.readTemperature();

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.println(temperature);

    if (temperature > tempThreshold) {
      digitalWrite(FAN_RELAY, HIGH);
    } else {
      digitalWrite(FAN_RELAY, LOW);
    }
  }
}

/* -------- Automatic Lighting Control -------- */
void lightingControl() {
  int ldrValue = analogRead(LDR_PIN);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < lightThreshold) {
    digitalWrite(LIGHT_RELAY, HIGH);
  } else {
    digitalWrite(LIGHT_RELAY, LOW);
  }
}

/* -------- Smoke Detection & Alarm -------- */
void smokeDetection() {
  int smokeValue = digitalRead(SMOKE_PIN);

  if (smokeValue == HIGH) {
    Serial.println("Smoke Detected!");
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

/* -------- Rain Detection -------- */
void rainDetection() {
  int rainValue = digitalRead(RAIN_PIN);

  if (rainValue == LOW) {
    Serial.println("Rain Detected - Retract Clothes Rope");
    // Motor logic can be added here
  }
}

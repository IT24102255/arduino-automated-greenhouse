#include <Arduino.h>
#include <DHT.h>

// SENSORS PIN DEFINE
#define DHT_PIN 27 // G27 PIN
#define LDR_PIN 33 // G33 PIN
#define SM_PIN 32 // G32 PIN

// ACTUATORS PIN DEFINE
#define HEATER_PIN 4 // G4 PIN
#define COOLER_PIN 5 // G5 PIN
#define DAY_LIGHT_PIN 17 // G17 PIN
#define WATER_PUMP_PIN 16 // G16 PIN

int TEMP_UPPER = 32;
int TEMP_LOWER = 28;
int LDR_THRESHOLD = 36;
int SM_THRESHOLD = 50;
int START_TIME = 0;
int END_TIME = 24;

DHT dhtSensor(DHT_PIN,DHT11);

void setup() {
  Serial.begin(115200);
  dhtSensor.begin();

}

void loop() {
  int smValue = analogRead(SM_PIN);
  int ldrValue = analogRead(LDR_PIN);
  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();

  float smPercentage = map(smValue, 0, 4095, 100, 0);
  float ldrPercentage = map(ldrValue. 0, 4095, 100, 0);

  int TEMP_THRESHOLD = (TEMP_UPPER + TEMP_LOWER) / 2;

  // COOLER HANDLER
  if (temperature > TEMP_UPPER) {
    digitalWrite(COOLER_PIN, LOW);
    Blynk.virtualWrite(V12, 1);

  } else if (temperature <= TEMP_THRESHOLD) {
    digitalWrite(COOLER_PIN, HIGH);
    Blynk.virtualWrite(V12, 0);

  }

  // HEATER HANDLER
  if (temperature < TEMP_LOWER) {
    digitalWrite(HEATER_PIN, LOW);
    Blynk.virtualWrite(V13, 1);

  } else if (temperature >= TEMP_THRESHOLD) {
    digitalWrite(HEATER_PIN, HIGH);
    Blynk.virtualWrite(V13, 0);

  }

  // DAY LIGHT HANDLER
  if (ldrPercentage < LDR_THRESHOLD && isTimeBetween(START_TIME, END_TIME)) {
    digitalWrite(DAY_LIGHT_PIN, LOW);
    Blynk.virtualWrite(V14, 1);

  } else {
    digitalWrite(DAY_LIGHT_PIN, HIGH);
    Blynk.virtualWrite(V14, 0);

  }

  // WATER PUMP HANDLER
  if (smPercentage < SM_THRESHOLD) {
    digitalWrite(WATER_PUMP_PIN, LOW);
    Blynk.virtualWrite(V15, 1);

  } else {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    Blynk.virtualWrite(V15, 0);

  }

  Serial.print("Soil moisture value: ");
  Serial.print(smPercentage);
  Serial.println("%");
  Serial.print("LDR percentage: ");
  Serial.print(ldrPercentage);
  Serial.println("%");
  Serial.print("Temperature value: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print(" \t Humidity value: ");
  Serial.print(humidity);
  Serial.println("% \n");

  delay(3000):

}

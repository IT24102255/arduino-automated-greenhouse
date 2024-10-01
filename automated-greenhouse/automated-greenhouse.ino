#include <Arduino.h>
#include <DHT.h>

// SENSORS PIN DEFINE
#define DHT_PIN 27 // G27 PIN
#define LDR_PIN 33 // G33 PIN
#define SM_PIN 32 // G32 PIN

void setup() {
  Serial.begin(115200);
  dhtSensor.begin();

}

void loop() {
  int smValue = analogRead(SM_PIN);
  int ldrValue = analogRead(LDR_PIN);
  float temperature = dhtSensor.readTemperature();
  float humidity = dhtSensor.readHumidity();

  Serial.print("Soil moisture value: ");
  Serial.println(smValue);
  Serial.print("LDR percentage: ");
  Serial.println(ldrValue);
  Serial.print("Temperature value: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print(" \t Humidity value: ");
  Serial.print(humidity);
  Serial.println("% \n");

  delay(3000):

}

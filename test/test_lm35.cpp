#include <Arduino.h>
#include <lm35.hpp>

LM35 temperature_sensor;

void setup() {
  temperature_sensor.set_pins(A0);
  temperature_sensor.initialize();
  Serial.begin(115200);
}

void loop() {
  Serial.print(temperature_sensor.read());
  Serial.println("*C");
  delay(500);
}
#include <Arduino.h>
#include <acs712.hpp>

ACS712 current_sensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing ACS712...");
  current_sensor.set_max_current(ACS712::MaxCurrent::Max20A);
  current_sensor.set_pins(A0);
  Serial.print("Initialized? ");
  Serial.println(current_sensor.initialize() ? "Yes" : "No");

  // You can change current unit using `set_unit` function
  // current_sensor.set_unit(ACS712::Unit::Milliamps);
}

void loop() {
  Serial.print("Readed current: ");
  Serial.print(current_sensor.read());
  Serial.println("A");
  delay(500);
}
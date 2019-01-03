#include <Arduino.h>
#include <joystick.hpp>

Orion::Joystick joy;

void setup() {
  joy.set_pins(A0, A1);
  joy.initialize();
  Serial.begin(115200);
}

void loop() {
  auto data = joy.read();
  Serial.print("X: ");
  Serial.print(data.x);
  Serial.print(", Y: ");
  Serial.println(data.y);
}

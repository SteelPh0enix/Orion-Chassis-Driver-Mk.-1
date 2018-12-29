#include <Arduino.h>
#include <button.hpp>
#include <wheel.hpp>

Orion::Wheel test_wheel{};

void setup() {
  Serial.begin(115200);
  test_wheel.set_pins(9, A0, A1);
  Serial.println(test_wheel.initialize() ? "Wheel initialized"
                                         : "Wheel not initialized");

  Button xd(12);
}

void loop() {}

#include <Arduino.h>
#include <motor.hpp>

Motor motor;

void setup() {
  motor.set_pins(9);
  motor.initialize();
  Serial.begin(115200);
}

void loop() {
  int i{0};
  for (; i <= 255; i++) {
    motor.set_speed(i);
    delay(10);
  }

  for (; i >= 0; i--) {
    motor.set_speed(i);
    delay(10);
  }
}

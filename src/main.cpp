#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <chassis.hpp>
#include <driving_algorithm.hpp>
#include <joypad_data_input.hpp>

using Chassis = Orion::Chassis<>;
using Input = JoypadDataInput<DefaultDriveAlgorithm>;

Input input(A10, A11);
Chassis chassis;

void setup() {
  Serial.begin(115200);

  input.initialize();
  chassis.set_data_input(&input);
  chassis.set_data_output(&Serial);

  chassis.initialize();
}

void loop() {
  if (Serial.available()) {
    chassis.drive();
  }
  chassis.interrupt();
}

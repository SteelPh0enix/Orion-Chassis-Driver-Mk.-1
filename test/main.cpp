#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <chassis.hpp>
#include <json_2axis_data_input.hpp>
#include <driving_algorithm.hpp>

using Chassis = Orion::Chassis<>;
using Input = Json2AxisDataInput<DefaultDriveAlgorithm>;

Input input;
Chassis chassis;

void setup() {
  Serial.begin(115200);

  input.set_data_input(&Serial);
  chassis.set_data_input(&input);
  chassis.set_data_output(&Serial);

  chassis.initialize();
}

void loop() {
  // if (Serial.available()) {
  //   char buffer[InputBufferSize];
  //   Serial.readBytesUntil('\n', buffer, InputBufferSize);
  //   auto des_result = ArduinoJson::deserializeJson(input_data, buffer);
  //   if (des_result == ArduinoJson::DeserializationError::Ok) {
  //     chassis.drive(input_data["SPD"].as<int>(),
  //     input_data["ROT"].as<int>());

  //     output_data["SPD"] = chassis.speed();
  //     output_data["ROT"] = chassis.rotation();
  //   }

  //   ArduinoJson::serializeJson(output_data, Serial);
  //   Serial.println();
  //   input_data.clear();
  //   output_data.clear();
  // }

  // chassis.interrupt();

  if (Serial.available()) {
    chassis.drive();
    }
  chassis.interrupt();
}

#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <chassis.hpp>

constexpr unsigned InputBufferSize{64};
constexpr unsigned OutputBufferSize{256};

using Chassis = Orion::Chassis<DefaultDriveAlgorithm>;

Chassis chassis;
ArduinoJson::StaticJsonDocument<InputBufferSize> input_data;
ArduinoJson::StaticJsonDocument<OutputBufferSize> output_data;

void setup() {
  Serial.begin(115200);
  chassis.initialize();
}

void loop() {
  if (Serial.available()) {
    char buffer[InputBufferSize];
    Serial.readBytesUntil('\n', buffer, InputBufferSize);
    auto des_result = ArduinoJson::deserializeJson(input_data, buffer);
    output_data["RET"] = des_result.c_str();
    if (des_result == ArduinoJson::DeserializationError::Ok) {
      chassis.drive(input_data["SPD"].as<int>(), input_data["ROT"].as<int>());
    }

    ArduinoJson::serializeJson(output_data, Serial);
    Serial.println();
    input_data.clear();
    output_data.clear();
  }

  chassis.interrupt();
}

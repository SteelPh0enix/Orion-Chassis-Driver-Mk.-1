#pragma once

#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <constants.hpp>
#include <data_input.hpp>

template <typename DrivingAlgorithm, unsigned BufferSize = 32>
class Json2AxisDataInput : public DataInput {
 public:
  Json2AxisDataInput(Stream* input = nullptr) { set_data_input(input); }

  void set_data_input(Stream* input) { m_input = input; }

  unsigned buffer_size() const { return BufferSize; }

  virtual ChassisDataInput data() const override {
    ChassisDataInput ret;
    auto chassis_data =
        m_algorithm.translate(m_buffer[Constant::Json::InputSpeed],
                              m_buffer[Constant::Json::InputRotation]);

    ret.left_front_speed = chassis_data.left_speed;
    ret.left_rear_speed = chassis_data.left_speed;
    ret.right_front_speed = chassis_data.right_speed;
    ret.right_rear_speed = chassis_data.right_speed;

    return ret;
  }

  virtual bool readData() override {
    m_buffer.clear();
    return ArduinoJson::deserializeJson(m_buffer, *m_input) ==
           ArduinoJson::DeserializationError::Ok;
  }

 private:
  DrivingAlgorithm m_algorithm;
  Stream* m_input{nullptr};
  ArduinoJson::StaticJsonDocument<BufferSize> m_buffer{};
};
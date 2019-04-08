#pragma once

#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <constants.hpp>
#include <data_input.hpp>

template <unsigned BufferSize = 256>
class JsonRawDataInput : public DataInput {
 public:
  JsonRawDataInput(Stream* input = nullptr) { set_data_input(input); }
  unsigned buffer_size() const { return BufferSize; }

  virtual ChassisDataInput data() const override {
    ChassisDataInput ret{};

    ret.left_front_speed = m_buffer[Constant::Json::LeftFrontWheelID];
    ret.left_rear_speed = m_buffer[Constant::Json::LeftRearWheelID];
    ret.right_front_speed = m_buffer[Constant::Json::RightFrontWheelID];
    ret.right_rear_speed = m_buffer[Constant::Json::RightRearWheelID];

    return ret;
  }

  //{"0":123}

  virtual bool readData() override {
    m_buffer.clear();
    // char raw_buffer[BufferSize];
    // m_input->readBytesUntil('\n', raw_buffer, BufferSize);
    return ArduinoJson::deserializeJson(m_buffer, *m_input) ==
           ArduinoJson::DeserializationError::Ok;
  }

  void set_data_input(Stream* input) { m_input = input; }

 private:
  Stream* m_input{nullptr};
  ArduinoJson::StaticJsonDocument<BufferSize> m_buffer{};
};
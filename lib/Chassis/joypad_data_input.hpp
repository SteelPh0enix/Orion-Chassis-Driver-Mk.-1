#pragma once

#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <constants.hpp>
#include <data_input.hpp>
#include <driving_algorithm.hpp>
#include <joypad.hpp>

template <typename DrivingAlgorithm>
class JoypadDataInput : public DataInput {
 public:
  JoypadDataInput(int x_axis, int y_axis) { set_pins(x_axis, y_axis); }

  void set_pins(int x_axis, int y_axis) { m_joypad.set_pins(x_axis, y_axis); }

  void initialize() {
    if (initialized()) return;
    m_joypad.initialize();
    m_joypad.calibrate();
    
    m_joypad.set_x_map_values(-512, 512, -250, 250);
    m_joypad.set_y_map_values(-512, 512, -250, 250);
    m_joypad.set_map_state(true);

    m_initialized = true;
  }

  virtual ChassisDataInput data() const override {
    ChassisDataInput ret;
    if (!initialized()) return ret;

    auto joypad_data = m_joypad.read();

    auto chassis_data = m_algorithm.translate(joypad_data.y, joypad_data.x);

    ret.left_front_speed = chassis_data.left_speed;
    ret.left_rear_speed = chassis_data.left_speed;
    ret.right_front_speed = chassis_data.right_speed;
    ret.right_rear_speed = chassis_data.right_speed;

    return ret;
  }

  virtual bool readData() override {
    if (!initialized()) return false;
    return true;
  }

  bool initialized() const { return m_initialized; }

 private:
  bool m_initialized{false};

  Joypad m_joypad{};

  DrivingAlgorithm m_algorithm{};
};
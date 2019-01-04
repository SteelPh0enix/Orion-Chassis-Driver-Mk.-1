#pragma once
#include <Arduino.h>
#include <stdint.h>

#include <wheel.hpp>

namespace Orion {
class Chassis {
 public:
  Chassis();
  void initialize();

  // set_speed allows to set forward/backward speed
  // Range: -255 : 255
  void set_speed(int16_t speed);
  int16_t speed() const;

  // set_rotation allows to set left/right rotation of chassis
  // Range: -255 : 255
  void set_rotation(int16_t value);
  int16_t rotation() const;

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  int16_t m_speed{};
  int16_t m_rotation{};
};
}  // namespace Orion
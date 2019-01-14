#pragma once
#include <Arduino.h>
#include <stdint.h>

#include <wheel.hpp>

namespace Orion {
class Chassis {
 public:

  struct WheelFeedback {
    Wheel::Feedback left_front;
    Wheel::Feedback right_front;
    Wheel::Feedback left_rear;
    Wheel::Feedback right_rear;
  };

  Chassis();
  void initialize();

  // This controls whole chassis.
  // Range of both values: -255 : 255
  void drive(int16_t speed, int16_t rotation);
  int16_t speed() const;
  int16_t rotation() const;

  WheelFeedback wheels_feedback() const;

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  int16_t m_speed{};
  int16_t m_rotation{};
};
}  // namespace Orion
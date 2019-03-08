#pragma once
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
  void drive(int speed, int rotation);
  int speed() const;
  int rotation() const;

  WheelFeedback wheels_feedback() const;

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  int m_speed{};
  int m_rotation{};
};
}  // namespace Orion
#pragma once
#include <Arduino.h>
#include <wheel.hpp>
#include <driving_algorithm.hpp>
#include "../../include/pinout.hpp"

namespace Orion {

template <typename DrivingAlgorithm>
class Chassis {
 public:
  struct WheelFeedback {
    Wheel::Feedback left_front;
    Wheel::Feedback right_front;
    Wheel::Feedback left_rear;
    Wheel::Feedback right_rear;
  };

  Chassis() {
    m_left_front_wheel.set_pins(Pinout::PWM_1, Pinout::DIR_1A, Pinout::DIR_1B,
                                Pinout::TEMPERATURE_1, Pinout::CURRENT_1);
    m_right_front_wheel.set_pins(Pinout::PWM_2, Pinout::DIR_2A, Pinout::DIR_2B,
                                 Pinout::TEMPERATURE_2, Pinout::CURRENT_2);
    m_left_rear_wheel.set_pins(Pinout::PWM_3, Pinout::DIR_3A, Pinout::DIR_3B,
                               Pinout::TEMPERATURE_3, Pinout::CURRENT_3);
    m_right_rear_wheel.set_pins(Pinout::PWM_4, Pinout::DIR_4A, Pinout::DIR_4B,
                                Pinout::TEMPERATURE_4, Pinout::CURRENT_4);
  }

  void initialize() {
    m_left_front_wheel.initialize();
    m_right_front_wheel.initialize();
    m_left_rear_wheel.initialize();
    m_right_rear_wheel.initialize();
  }

  // This controls whole chassis.
  // Range of both values: -255 : 255
  void drive(int speed, int rotation) {
    auto wheel_data = m_algorithm.translate(speed, rotation);

    m_left_front_wheel.set_speed(wheel_data.left_speed);
    m_left_rear_wheel.set_speed(wheel_data.left_speed);
    m_right_front_wheel.set_speed(wheel_data.right_speed);
    m_right_rear_wheel.set_speed(wheel_data.right_speed);

    m_speed = speed;
    m_rotation = rotation;
  }
  int speed() const { return m_speed; }
  int rotation() const { return m_rotation; }

  WheelFeedback wheels_feedback() const {
    return {m_left_front_wheel.feedback(), m_right_front_wheel.feedback(),
            m_left_rear_wheel.feedback(), m_right_rear_wheel.feedback()};
  }

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  int m_speed{};
  int m_rotation{};

  DrivingAlgorithm m_algorithm;
};
}  // namespace Orion
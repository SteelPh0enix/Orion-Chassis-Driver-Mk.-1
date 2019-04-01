#pragma once
#include <Arduino.h>
#include <driving_algorithm.hpp>
#include <wheel.hpp>
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

    if (self_test_state())
      self_test();
  }

  void self_test() {
    m_left_front_wheel.set_speed(100);
    m_left_rear_wheel.set_speed(100);
    m_right_front_wheel.set_speed(100);
    m_right_rear_wheel.set_speed(100);

    delay(2000);

    m_left_front_wheel.set_speed(-100);
    m_left_rear_wheel.set_speed(-100);
    m_right_front_wheel.set_speed(-100);
    m_right_rear_wheel.set_speed(-100);

    delay(2000);

    m_left_front_wheel.set_speed(0);
    m_left_rear_wheel.set_speed(0);
    m_right_front_wheel.set_speed(0);
    m_right_rear_wheel.set_speed(0);
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

  void set_self_test(bool state) { m_self_test = state; }
  bool self_test_state() const { return m_self_test; }

  WheelFeedback wheels_feedback() const {
    return {m_left_front_wheel.feedback(), m_right_front_wheel.feedback(),
            m_left_rear_wheel.feedback(), m_right_rear_wheel.feedback()};
  }

  int interrupt_delay() const { return m_interrupt_delay; }
  void set_interrupt_delay(int delay) { m_interrupt_delay = delay; }

  void interrupt() {
    if (m_next_interrupt > m_last_interrupt + interrupt_delay())
      return;

    m_left_front_wheel.interrupt();
    m_right_front_wheel.interrupt();
    m_left_rear_wheel.interrupt();
    m_right_rear_wheel.interrupt();

    m_last_interrupt = millis();
    m_next_interrupt = m_last_interrupt + interrupt_delay();
  }

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  int m_speed{};
  int m_rotation{};

  DrivingAlgorithm m_algorithm;

  bool m_self_test{false};

  int m_interrupt_delay{100};
  unsigned long long m_last_interrupt{};
  unsigned long long m_next_interrupt{};
};
}  // namespace Orion
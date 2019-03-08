/*
    Typical PWM-controlled motor class
*/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../module.hpp"

class Motor : public Module {
 public:
  enum class Direction { None, Forward, Backward };

  Motor() = default;
  Motor(unsigned pwm_pin, unsigned direction_a_pin, unsigned direction_b_pin,
        bool init = true);

  bool initialize();
  void set_pins(unsigned pwm_pin, unsigned direction_a_pin,
                unsigned direction_b_pin);

  // Range: -255 : 255
  void set_speed(int speed);
  // Speed will always be positive. Check direction to see, which way wheel
  // rotates
  int speed() const;

  // This is automatically called at set_speed, but i'll
  // let it be public
  void set_direction(Direction direction);
  Direction direction() const;

 private:
  unsigned m_pwm_pin{};
  unsigned m_direction_a{};
  unsigned m_direction_b{};

  int m_speed{};

  Direction m_direction{Direction::None};
};
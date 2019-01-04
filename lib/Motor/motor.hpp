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
  Motor(uint8_t pwm_pin, uint8_t direction_a_pin, uint8_t direction_b_pin,
        bool init = true);

  bool initialize();
  void set_pins(uint8_t pwm_pin, uint8_t direction_a_pin,
                uint8_t direction_b_pin);

  void set_speed(int16_t speed);
  // Speed will always be positive. Check direction to see, which way wheel
  // rotates
  int16_t speed() const;

  // This is automatically called at set_speed, but i'll
  // let it be public
  void set_direction(Direction direction);
  Direction direction() const;

 private:
  uint8_t m_pwm_pin{};
  uint8_t m_direction_a{};
  uint8_t m_direction_b{};

  int16_t m_speed{};

  Direction m_direction{Direction::None};
};
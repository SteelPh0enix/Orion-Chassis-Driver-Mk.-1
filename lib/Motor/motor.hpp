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
  Motor(unsigned pwm_pin,
        unsigned direction_a_pin,
        unsigned direction_b_pin,
        bool init = true);

  bool initialize();
  void set_pins(unsigned pwm_pin,
                unsigned direction_a_pin,
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

  bool slow_mode() const;
  void set_slow_mode(bool mode);

  int slow_mode_increment() const;
  void set_slow_mode_increment(int inc);

  // In case of slow-mode operation, call this inside interrupt.
  void interrupt();

 private:
  unsigned m_pwm_pin{};
  unsigned m_direction_a{};
  unsigned m_direction_b{};

  int m_speed{};
  int m_designated_speed{};

  Direction m_direction{Direction::None};

  bool m_slow_mode{true};
  int m_slow_mode_increment{10};

  void set_speed_instant(int speed);
  void set_speed_slow(int speed);
};
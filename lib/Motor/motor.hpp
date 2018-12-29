/*
    Typical PWM-controlled motor class
*/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../module.hpp"

class Motor : public Module {
 public:
  Motor() = default;
  Motor(uint8_t pwm_pin, bool init = true);

  bool initialize();
  void set_pins(uint8_t pwm_pin);

  void set_speed(uint8_t speed);
  uint8_t speed() const;

 private:
  uint8_t m_pwm_pin{};
  uint8_t m_speed{};
};
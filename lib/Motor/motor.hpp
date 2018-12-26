/*
    Typical PWM-controlled motor class
*/

#pragma once

#include <Arduino.h>
#include <stdint.h>

class Motor {
 public:
  Motor() = default;
  Motor(uint8_t pwm_pin, bool init = true);

  bool initialize();
  bool initialized() const;

  void set_pins(uint8_t pwm_pin);
  bool pins_set() const;

  void set_speed(uint8_t speed);
  uint8_t speed() const;

 private:
  uint8_t m_pwm_pin{};
  bool m_initialized{false};
  bool m_pins_set{false};

  uint8_t m_speed{};
};
#include "motor.hpp"

Motor::Motor(uint8_t pwm_pin, bool init) {
  set_pins(pwm_pin);
  if (init) initialize();
}

bool Motor::initialize() {
  if (!pins_set()) return false;

  pinMode(m_pwm_pin, OUTPUT);
  m_initialized = true;
  return true;
}

bool Motor::initialized() const { return m_initialized; }

void Motor::set_pins(uint8_t pwm_pin) {
  m_pwm_pin = pwm_pin;
  m_pins_set = true;
}

bool Motor::pins_set() const { return m_pins_set; }

void Motor::set_speed(uint8_t speed) {
  analogWrite(m_pwm_pin, speed);
  m_speed = speed;
}

uint8_t Motor::speed() const { return m_speed; }
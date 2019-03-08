#include "motor.hpp"

Motor::Motor(unsigned pwm_pin, unsigned direction_a_pin,
             unsigned direction_b_pin, bool init) {
  set_pins(pwm_pin, direction_a_pin, direction_b_pin);
  if (init) initialize();
}

bool Motor::initialize() {
  if (!pins_set()) return false;

  pinMode(m_pwm_pin, OUTPUT);
  pinMode(m_direction_a, OUTPUT);
  pinMode(m_direction_b, OUTPUT);

  m_initialized = true;
  return true;
}

void Motor::set_pins(unsigned pwm_pin, unsigned direction_a_pin,
                     unsigned direction_b_pin) {
  m_pwm_pin = pwm_pin;
  m_direction_a = direction_a_pin;
  m_direction_b = direction_b_pin;

  m_pins_set = true;
}

void Motor::set_speed(int speed) {
  if (speed < 0) {
    set_direction(Direction::Backward);
    speed *= -1;
  } else if (speed == 0) {
    set_direction(Direction::None);
  } else {
    set_direction(Direction::Forward);
  }

  if (speed > 255) speed = 255;
  analogWrite(m_pwm_pin, speed);
  m_speed = speed;
}

int Motor::speed() const { return m_speed; }

void Motor::set_direction(Motor::Direction direction) {
  switch (direction) {
    case Direction::None: {
      digitalWrite(m_direction_a, 0);
      digitalWrite(m_direction_b, 0);
      break;
    }
    case Direction::Forward: {
      digitalWrite(m_direction_a, 1);
      digitalWrite(m_direction_b, 0);
      break;
    }
    case Direction::Backward: {
      digitalWrite(m_direction_a, 0);
      digitalWrite(m_direction_b, 1);
      break;
    }
  }
}

Motor::Direction Motor::direction() const { return m_direction; }
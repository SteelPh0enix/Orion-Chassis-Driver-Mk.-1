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
  if (slow_mode()) {
    set_speed_slow(speed);
  } else {
    set_speed_instant(speed);
  }
}

void Motor::set_speed_instant(int speed) {
  m_speed = speed;

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
}

void Motor::set_speed_slow(int speed) { m_designated_speed = speed; }

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

bool Motor::slow_mode() const { return m_slow_mode; }

void Motor::set_slow_mode(bool mode) { m_slow_mode = mode; }

int Motor::slow_mode_increment() const { return m_slow_mode_increment; }

void Motor::set_slow_mode_increment(int inc) { m_slow_mode_increment = inc; }

template <typename T>
constexpr int sign(T value) {
  return value >= 0 ? 1 : -1;
}

void Motor::interrupt() {
  // Check if actual and designated speed difference is big enought to change it
  if (abs(m_designated_speed - m_speed) < m_slow_mode_increment) return;

  // Edge case: designated value close to 0 fails with this method, so i have
  // to do some tricks in order to prevent it.
  if (abs(m_designated_speed) < m_slow_mode_increment) {
    m_designated_speed = 0;
  }

  int difference_sign{sign(m_designated_speed)};
  // Edge case: as above, if we are aiming for 0 and speed is positive (which
  // normally would make difference_sign also positive, and make motor go faster
  // instead of slowing down), change the sign to prevent bugging.
  if (m_designated_speed == 0 && m_speed > 0) difference_sign *= -1;

  set_speed_instant(m_speed + (m_slow_mode_increment * difference_sign));
}
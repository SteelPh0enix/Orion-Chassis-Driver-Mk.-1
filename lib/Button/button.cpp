#include "button.hpp"

Button::Button(uint8_t pin, bool init) {
  set_pins(pin);
  if (init) initialize();
}

bool Button::initialize() {
  if (!pins_set()) return false;

  pinMode(m_pin, INPUT_PULLUP);
  refresh_state();
  m_initialized = true;
  return true;
}

void Button::set_pins(uint8_t pin) {
  m_pin = pin;
  m_pins_set = true;
}

bool Button::pressed() const {
  if (!initialized()) {
    return false;
  }
  // INPUT_PULLUP negates the readings
  return !digitalRead(m_pin);
}

void Button::refresh_state() {
  if (initialized()) {
    m_state = !digitalRead(m_pin);
  }
}

bool Button::state_changed() const {
  if (!initialized()) {
    return false;
  }

  // Because of pullup, this would end as double negation, so == is valid
  return last_state() == digitalRead(m_pin);
}

bool Button::last_state() const { return m_state; }
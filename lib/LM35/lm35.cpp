#include "lm35.hpp"

LM35::LM35(unsigned input_pin, bool init) {
  set_pins(input_pin);
  if (init) {
    initialize();
  }
}

bool LM35::initialize() {
  if (initialized()) return true;
  if (!pins_set()) return false;

  pinMode(m_input_pin, INPUT);
  m_initialized = true;
  return true;
}

void LM35::set_pins(unsigned input_pin) {
  m_input_pin = input_pin;
  m_pins_set = true;
}

double LM35::read() const {
  if (!initialized()) return 0.;

  return voltage_to_temperature(analogRead(m_input_pin));
}

double LM35::voltage_to_temperature(int voltage) const {
  // (* 100) is used to normalize temperature (sensor yields 10mV per degree).
  return (static_cast<double>(voltage) * 5.0 / ADC_MAX_VALUE) * 100;
}
#include "analog_control.hpp"
#include <Arduino.h>

AnalogControl::AnalogControl(unsigned pin, bool init) {
  set_pins(pin);
  if (init) initialize();
}

bool AnalogControl::initialize() {
  if (!pins_set()) return false;

  pinMode(m_pin, INPUT);
  m_initialized = true;
  return true;
}

void AnalogControl::set_pins(unsigned pin) {
  m_pin = pin;
  m_pins_set = true;
}

void AnalogControl::calibrate() { m_calibration = read_raw(); }

int AnalogControl::read_raw() const { return analogRead(m_pin); }

int AnalogControl::read() const {
  int value = normalize(read_raw());
  if (map_state()) {
    return map(value, m_from_min, m_from_max, m_to_min, m_to_max);
  }
  return value;
}

int AnalogControl::normalize(int value) const { return value - m_calibration; }

unsigned AnalogControl::pin() const { return m_pin; }

void AnalogControl::set_map_state(bool map_state) { m_map_state = map_state; }

bool AnalogControl::map_state() const { return m_map_state; }

void AnalogControl::set_map_values(long from_min, long from_max, long to_min,
                                   long to_max) {
  m_from_min = from_min;
  m_from_max = from_max;
  m_to_min = to_min;
  m_to_max = to_max;
}
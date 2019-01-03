#include "joystick.hpp"

namespace Orion {
Joystick::Joystick(uint8_t x_axis, uint8_t y_axis, bool init) {
  set_pins(x_axis, y_axis);
  if (init) initialize();
}

void Joystick::set_pins(uint8_t x_axis, uint8_t y_axis) {
  m_x_axis = x_axis;
  m_y_axis = y_axis;
  m_pins_set = true;
}

bool Joystick::initialize() {
  if (!pins_set()) return false;
  pinMode(m_x_axis, INPUT);
  pinMode(m_y_axis, INPUT);
  m_initialized = true;
  return m_initialized;
}

int16_t Joystick::x_axis() const {
  return normalize_read(analogRead(m_x_axis));
}

int16_t Joystick::y_axis() const {
  return normalize_read(analogRead(m_y_axis));
}

Joystick::Data Joystick::read() const { return {x_axis(), y_axis()}; }

inline int16_t Joystick::normalize_read(int16_t value) const {
  // Just push the value by half of ADC range so the middle point will be at 0.
  // In theory.
  return value - (static_cast<int16_t>(ADC_MAX_VALUE) / 2);
}

}  // namespace Orion
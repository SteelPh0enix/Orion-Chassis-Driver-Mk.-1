#include "joypad.hpp"
#include <Arduino.h>

Joypad::Joypad(unsigned x_axis, unsigned y_axis, bool init) {
  set_pins(x_axis, y_axis);
  if (init) initialize();
}

void Joypad::set_pins(unsigned x_axis, unsigned y_axis) {
  m_x_axis.set_pins(x_axis);
  m_y_axis.set_pins(y_axis);
  m_pins_set = true;
}

bool Joypad::initialize() {
  if (!pins_set()) return false;
  m_x_axis.initialize();
  m_y_axis.initialize();
  m_initialized = true;
  return true;
}

void Joypad::calibrate() {
  calibrate_x();
  calibrate_y();
}

void Joypad::calibrate_x() { m_x_axis.calibrate(); }
void Joypad::calibrate_y() { m_y_axis.calibrate(); }

inline int Joypad::x_axis_raw() const { return m_x_axis.read_raw(); }
inline int Joypad::y_axis_raw() const { return m_y_axis.read_raw(); }

inline int Joypad::x_axis() const {
  return m_invert_x ? -m_x_axis.read() : m_x_axis.read();
}

inline int Joypad::y_axis() const {
  return m_invert_y ? -m_y_axis.read() : m_y_axis.read();
}

Joypad::Data Joypad::read_raw() const { return {x_axis_raw(), y_axis_raw()}; }
Joypad::Data Joypad::read() const { return {x_axis(), y_axis()}; }

unsigned Joypad::x_pin() const { return m_x_axis.pin(); }
unsigned Joypad::y_pin() const { return m_y_axis.pin(); }

void Joypad::invert_x(bool inv) { m_invert_x = inv; }
void Joypad::invert_y(bool inv) { m_invert_y = inv; }

void Joypad::set_map_state(bool map_state) {
  m_x_axis.set_map_state(map_state);
  m_y_axis.set_map_state(map_state);
}

bool Joypad::map_state() const { return m_x_axis.map_state(); }

void Joypad::set_x_map_values(long from_min, long from_max, long to_min,
                              long to_max) {
  m_x_axis.set_map_values(from_min, from_max, to_min, to_max);
}

void Joypad::set_y_map_values(long from_min, long from_max, long to_min,
                              long to_max) {
  m_y_axis.set_map_values(from_min, from_max, to_min, to_max);
}
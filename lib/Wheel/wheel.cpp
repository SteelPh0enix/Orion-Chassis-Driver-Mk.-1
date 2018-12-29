#include "wheel.hpp"

namespace Orion {

Wheel::Wheel() {
  m_current_sensor.set_max_current(ACS712::MaxCurrent::Max30A);
  m_current_sensor.set_unit(ACS712::Unit::Amps);
}

Wheel::Wheel(uint8_t motor_pin, uint8_t temperature_sensor_pin,
             uint8_t current_sensor_pin, bool init) {
  m_current_sensor.set_max_current(ACS712::MaxCurrent::Max30A);
  m_current_sensor.set_unit(ACS712::Unit::Amps);
  set_pins(motor_pin, temperature_sensor_pin, current_sensor_pin);
  if (init) initialize();
}

bool Wheel::initialize() {
  if (!pins_set()) return false;
  return m_current_sensor.initialize() && m_temperature_sensor.initialize() &&
         m_motor.initialize();
}

bool Wheel::initialized() const {
  return m_current_sensor.initialized() && m_temperature_sensor.initialized() &&
         m_motor.initialized();
}

void Wheel::set_pins(uint8_t motor_pin, uint8_t temperature_sensor_pin,
                     uint8_t current_sensor_pin) {
  m_current_sensor.set_pins(current_sensor_pin);
  m_temperature_sensor.set_pins(temperature_sensor_pin);
  m_motor.set_pins(motor_pin);
}

bool Wheel::pins_set() const {
  return m_current_sensor.pins_set() && m_temperature_sensor.pins_set() &&
         m_motor.pins_set();
}
}  // namespace Orion
/*
    Orion wheel (Motor + temperature sensor + current sensor) class
*/

#pragma once

#include <Arduino.h>
#include <acs712.hpp>
#include <lm35.hpp>
#include <motor.hpp>

namespace Orion {
class Wheel {
 public:
  struct Feedback {
    double temperature;
    double current;
    uint8_t speed;
  };

  Wheel();
  Wheel(uint8_t motor_pin, uint8_t temperature_sensor_pin,
        uint8_t current_sensor_pin, bool init = true);

  bool initialize();
  bool initialized() const;

  void set_pins(uint8_t motor_pin, uint8_t temperature_sensor_pin,
                uint8_t current_sensor_pin);
  bool pins_set() const;

 private:
  ACS712 m_current_sensor{};
  LM35 m_temperature_sensor{};
  Motor m_motor{};
};
}  // namespace Orion
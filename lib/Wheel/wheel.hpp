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
  // Structure containing full wheel feedback data
  struct Feedback {
    double temperature;
    double current;
    uint8_t speed;
  };

  Wheel();
  Wheel(uint8_t motor_pin, uint8_t motor_dir_a_pin, uint8_t motor_dir_b_pin, uint8_t temperature_sensor_pin,
        uint8_t current_sensor_pin, bool init = true);

  bool initialize();
  bool initialized() const;

  void set_pins(uint8_t motor_pin, uint8_t motor_dir_a_pin, uint8_t motor_dir_b_pin, uint8_t temperature_sensor_pin,
                uint8_t current_sensor_pin);
  bool pins_set() const;

  // Functions for reading the data from wheel
  // Current in amps, temperature in celcius
  double current() const;
  double temperature() const;
  uint8_t speed() const;
  Feedback feedback() const;

  void set_speed(uint8_t speed);

 private:
  ACS712 m_current_sensor{};
  LM35 m_temperature_sensor{};
  Motor m_motor{};
};
}  // namespace Orion
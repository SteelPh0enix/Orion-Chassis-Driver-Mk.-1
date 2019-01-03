/*
    Orion manual chasis controller (joystick) class
*/

#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "../module.hpp"

namespace Orion {
class Joystick : public Module {
 public:
  struct Data {
    int16_t x, y;
  };

  Joystick() = default;
  Joystick(uint8_t x_axis, uint8_t y_axis, bool init = true);

  void set_pins(uint8_t x_axis, uint8_t y_axis);
  virtual bool initialize() override;

  // Functions for reading data on specific axis
  int16_t x_axis() const;
  int16_t y_axis() const;

  // Function returning data from both axis
  Data read() const;

 private:
  inline int16_t normalize_read(int16_t value) const;

  uint8_t m_x_axis{};
  uint8_t m_y_axis{};
};
}  // namespace Orion

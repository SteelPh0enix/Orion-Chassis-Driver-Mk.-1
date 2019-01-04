#pragma once
#include <Arduino.h>
#include <stdint.h>

#include <wheel.hpp>
#include <pinout.hpp>

namespace Orion {
class Chassis {
  public:
    Chassis();
    void initialize();

    // set_speed allows to set forward/backward speed
    void set_speed();

    
    void set_rotation();

  private:
    Wheel m_left_front_wheel;
    Wheel m_right_front_wheel;
    Wheel m_left_rear_wheel;
    Wheel m_right_rear_wheel;
};
}  // namespace Orion
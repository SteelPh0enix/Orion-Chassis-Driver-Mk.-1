#include "chassis.hpp"

#include <pinout.hpp>

namespace Orion {
Chassis::Chassis() {
  m_left_front_wheel.set_pins(Pinout::PWM_1, Pinout::DIR_1A, Pinout::DIR_1B,
                              Pinout::TEMPERATURE_1, Pinout::CURRENT_1);
  m_right_front_wheel.set_pins(Pinout::PWM_2, Pinout::DIR_2A, Pinout::DIR_2B,
                               Pinout::TEMPERATURE_2, Pinout::CURRENT_2);
  m_left_rear_wheel.set_pins(Pinout::PWM_3, Pinout::DIR_3A, Pinout::DIR_3B,
                               Pinout::TEMPERATURE_3, Pinout::CURRENT_3);
  m_right_rear_wheel.set_pins(Pinout::PWM_4, Pinout::DIR_4A, Pinout::DIR_4B,
                               Pinout::TEMPERATURE_4, Pinout::CURRENT_4);
}
}  // namespace Orion
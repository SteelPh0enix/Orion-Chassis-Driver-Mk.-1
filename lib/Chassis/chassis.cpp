#include "chassis.hpp"

#include "../../include/pinout.hpp"

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

void Chassis::initialize() {
  m_left_front_wheel.initialize();
  m_right_front_wheel.initialize();
  m_left_rear_wheel.initialize();
  m_right_rear_wheel.initialize();
}

void Chassis::drive(int16_t speed, int16_t rotation) {
  m_left_front_wheel.set_speed(speed + rotation);
  m_right_front_wheel.set_speed(speed - rotation);
  m_left_rear_wheel.set_speed(speed + rotation);
  m_right_rear_wheel.set_speed(speed - rotation);

  m_speed = speed;
  m_rotation = rotation;
}

int16_t Chassis::speed() const { return m_speed; }
int16_t Chassis::rotation() const { return m_rotation; }

Chassis::WheelFeedback Chassis::wheels_feedback() const {
  return {
    m_left_front_wheel.feedback(),
    m_right_front_wheel.feedback(),
    m_left_rear_wheel.feedback(),
    m_right_rear_wheel.feedback()
  };
}

}  // namespace Orion
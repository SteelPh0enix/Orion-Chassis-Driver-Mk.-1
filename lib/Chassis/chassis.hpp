#pragma once
#include <Arduino.h>
#include <constants.hpp>
#include <data_input.hpp>
#include <driving_algorithm.hpp>
#include <wheel.hpp>
#include "../../include/pinout.hpp"

namespace Orion {

template <unsigned FeedbackMaxSize = 256>
class Chassis {
 public:
  struct WheelFeedback {
    Wheel::Feedback left_front;
    Wheel::Feedback right_front;
    Wheel::Feedback left_rear;
    Wheel::Feedback right_rear;
  };

  Chassis(DataInput* data_input = nullptr, Stream* data_output = nullptr) {
    m_left_front_wheel.set_pins(Pinout::PWM_1, Pinout::DIR_1A, Pinout::DIR_1B,
                                Pinout::TEMPERATURE_1, Pinout::CURRENT_1);
    m_right_front_wheel.set_pins(Pinout::PWM_2, Pinout::DIR_2A, Pinout::DIR_2B,
                                 Pinout::TEMPERATURE_2, Pinout::CURRENT_2);
    m_left_rear_wheel.set_pins(Pinout::PWM_3, Pinout::DIR_3A, Pinout::DIR_3B,
                               Pinout::TEMPERATURE_3, Pinout::CURRENT_3);
    m_right_rear_wheel.set_pins(Pinout::PWM_4, Pinout::DIR_4A, Pinout::DIR_4B,
                                Pinout::TEMPERATURE_4, Pinout::CURRENT_4);

    set_data_input(data_input);
    set_data_output(data_output);
  }

  void initialize() {
    m_left_front_wheel.initialize();
    m_right_front_wheel.initialize();
    m_left_rear_wheel.initialize();
    m_right_rear_wheel.initialize();
  }

  // This controls whole chassis.
  // Range of both values: -255 : 255
  // void drive(int speed, int rotation) {
  //   auto wheel_data = m_algorithm.translate(speed, rotation);

  //   m_left_front_wheel.set_speed(wheel_data.left_speed);
  //   m_left_rear_wheel.set_speed(wheel_data.left_speed);
  //   m_right_front_wheel.set_speed(wheel_data.right_speed);
  //   m_right_rear_wheel.set_speed(wheel_data.right_speed);

  //   m_speed = speed;
  //   m_rotation = rotation;
  // }

  void drive() {
    if (!m_data_input->readData()) {
      m_data_output->println(Constant::Error::ReadingChassisData);
      return;
    }

    ChassisDataInput wheel_data = m_data_input->data();
    m_left_front_wheel.set_speed(wheel_data.left_front_speed);
    m_right_front_wheel.set_speed(wheel_data.right_front_speed);
    m_left_rear_wheel.set_speed(wheel_data.left_rear_speed);
    m_right_rear_wheel.set_speed(wheel_data.right_rear_speed);
  }

  WheelFeedback wheels_feedback() const {
    return {m_left_front_wheel.feedback(), m_right_front_wheel.feedback(),
            m_left_rear_wheel.feedback(), m_right_rear_wheel.feedback()};
  }

  unsigned long interrupt_delay() const { return m_interrupt_delay; }
  void set_interrupt_delay(int delay) {
    m_interrupt_delay = delay;
    update_interrupt_counter();
  }

  bool check_interrupt() { return millis() >= m_next_interrupt; }

  void interrupt() {
    if (!check_interrupt()) {
      return;
    }

    m_left_front_wheel.interrupt();
    m_right_front_wheel.interrupt();
    m_left_rear_wheel.interrupt();
    m_right_rear_wheel.interrupt();

    update_interrupt_counter();
    print_feedback();
  }

  void update_interrupt_counter() {
    m_next_interrupt = millis() + interrupt_delay();
  }

  void print_feedback() {
    ArduinoJson::StaticJsonDocument<FeedbackMaxSize> feedback_buffer;
    auto left_front_obj =
        feedback_buffer.createNestedObject(Constant::Json::LeftFrontWheelID);
    populate_wheel_feedback(m_left_front_wheel, left_front_obj);

    auto left_rear_obj =
        feedback_buffer.createNestedObject(Constant::Json::LeftRearWheelID);
    populate_wheel_feedback(m_left_rear_wheel, left_rear_obj);

    auto right_front_obj =
        feedback_buffer.createNestedObject(Constant::Json::RightFrontWheelID);
    populate_wheel_feedback(m_right_front_wheel, right_front_obj);

    auto right_rear_obj =
        feedback_buffer.createNestedObject(Constant::Json::RightRearWheelID);
    populate_wheel_feedback(m_right_rear_wheel, right_rear_obj);

    ArduinoJson::serializeJson(feedback_buffer, *m_data_output);
    Serial.println();
  }

  unsigned feedback_max_size() const { return FeedbackMaxSize; }

  void set_data_input(DataInput* input) { m_data_input = input; }

  void set_data_output(Stream* output) { m_data_output = output; }

 private:
  Wheel m_left_front_wheel;
  Wheel m_right_front_wheel;
  Wheel m_left_rear_wheel;
  Wheel m_right_rear_wheel;

  unsigned long m_interrupt_delay{100};
  unsigned long m_next_interrupt{};

  DataInput* m_data_input{nullptr};
  Stream* m_data_output{nullptr};

  void populate_wheel_feedback(Wheel& wheel, ArduinoJson::JsonObject& obj) {
    obj[Constant::Json::Speed] = wheel.speed();
    obj[Constant::Json::Current] = wheel.current();
    obj[Constant::Json::Temperature] = wheel.temperature();
  }
};
}  // namespace Orion
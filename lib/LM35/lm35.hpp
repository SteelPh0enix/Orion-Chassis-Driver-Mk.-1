/*
    LM35 analog thermometer class
*/

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../module.hpp"

class LM35 : public Module {
  // This constans indicates analogRead max value. Change it to 4096 when
  // dealing with Arduino Due or similar boards, which have 12-bit ADC.
  constexpr static double ADC_MAX_VALUE{1024.};

 public:
  // Default c-tor
  LM35() = default;

  // Pin-setting and initializing c-tor
  LM35(unsigned input_pin, bool init = true);

  // Initializes the object and Arduino peripherals.
  // Returns false, if initialization failed.
  virtual bool initialize() override;

  // Set pin for input
  void set_pins(unsigned input_pin);

  // Actual functionality

  // In case of error it will always return 0.
  // Remember to set pins and initialize the object before
  // trying to read any meaningful value.
  double read() const;

 private:
  double voltage_to_temperature(int voltage) const;

  unsigned m_input_pin{};
};
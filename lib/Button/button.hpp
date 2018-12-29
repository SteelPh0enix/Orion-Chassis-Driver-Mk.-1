#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "../module.hpp"

class Button : public Module {
 public:
  Button() = default;
  Button(uint8_t pin, bool init = true);

  virtual bool initialize() override;
  void set_pins(uint8_t pin);

  bool pressed() const;

  // These two functions are connected to each other.
  // `refresh_state` is called at `initialize`, and it gets
  // first state of button.
  // Then, you can call it to refresh this state, which is kept internally
  // in object.
  // `state_changed` checks if the state of button in the moment of calling this
  // function is different than last state, and returns `true` if so, or `false`
  // if it's the same as before. It does not refresh the state itself.
  void refresh_state();
  bool state_changed() const;
  bool last_state() const;

 private:
  bool m_state{};
  uint8_t m_pin{};
};
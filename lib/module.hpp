/*
  Base class for every module i've written code to.
  Contains pin settings and intialization.

  Created in order to write less boilerplate for every class.
*/

#pragma once

class Module {
 public:
  virtual ~Module() = default;

  // Every device have to override this function
  virtual bool initialize() = 0;

  // Getters
  bool initialized() const { return m_initialized; }
  bool pins_set() const { return m_pins_set; }

  // Since every device will probably need different pin settings, and
  // i don't want to mess with templates on AVR's too much,
  // set_pins function will not be available in this class.
 protected:
  bool m_initialized{false};
  bool m_pins_set{false};

  // This constans indicates analogRead max value. Change it to 4096 when
  // dealing with Arduino Due or similar boards, which have 12-bit ADC.
  constexpr static double ADC_MAX_VALUE{1024.};
};
#pragma once
#include "../module.hpp"

/*
  Class for abstract analog control module, with calibration
*/

class AnalogControl : public Module {
 public:
  AnalogControl() = default;
  AnalogControl(unsigned pin, bool init = true);

  virtual bool initialize() override;
  void set_pins(unsigned pin);

  // This function calibrates the analog control according to actual state
  void calibrate();

  // This function allows to set custom calibration value
  void set_calibration_value(int value);

  int read_raw() const;
  int read() const;

  unsigned pin() const;

  void set_map_state(bool map_state);
  void set_map_values(long from_min, long from_max, long to_min, long to_max);
  bool map_state() const;

 protected:
  int normalize(int value) const;

  unsigned m_pin{};

  int m_calibration{0};

  long m_from_min, m_from_max, m_to_min, m_to_max;
  bool m_map_state{false};
};
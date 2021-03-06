#pragma once
#include "../AnalogControl/analog_control.hpp"

/*
  Joypad class
*/

class Joypad : public Module {
 public:
  // Structures
  struct Data {
    int x, y;
  };

  // Constructors
  Joypad() = default;
  Joypad(unsigned x_axis, unsigned y_axis, bool init = true);

  // Initalization and calibration
  void set_pins(unsigned x_axis, unsigned y_axis);
  virtual bool initialize() override;

  // This function reads joypad value and sets it as `0` reference.
  // By default, it's half of ADC max value.
  void calibrate();

  // Those functions calibrate the axes
  void calibrate_x();
  void calibrate_y();

  // Same as above, but without normalization
  inline int x_axis_raw() const;
  inline int y_axis_raw() const;

  // Read and normalize data from X and Y axis
  inline int x_axis() const;
  inline int y_axis() const;

  // Read non-normalized data (straight analogRead)
  Data read_raw() const;

  // Read normalized data from joypad
  Data read() const;

  unsigned x_pin() const;
  unsigned y_pin() const;

  // This function inverts sign of returned value from pad X and Y axes
  void invert_x(bool inv);
  void invert_y(bool inv);

  void set_map_state(bool map_state);
  bool map_state() const;

  void set_x_map_values(long from_min, long from_max, long to_min, long to_max);
  void set_y_map_values(long from_min, long from_max, long to_min, long to_max);

 protected:
  AnalogControl m_x_axis{}, m_y_axis{};

  bool m_invert_x{false};
  bool m_invert_y{false};
};

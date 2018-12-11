/*
    ACS712 current sensor class

    Description:
        This class allows to easely use ACS712 current sensor.
    
    Initialization:
        Create ACS712 object, either using default constructor or parametrized.
        After using default c-tor, you will have to set pins and initialize the object
        using `set_pins`, `set_max_current` and `initialize` functions.
        Alternatively, you can use second c-tor which allows you to set pins, current and 
        initialize the object at once.

        Always call `initialize` AFTER you have set the pins and max current.

        Every function using Arduino peripherals will check if object if initialized,
        and return `false`, default or invalid value if it's not (see function comments)

        You can check the state of object with `pins_set` and `initialized`
        functions.

        Don't forget to set max current your ACS712 can measure, because if you
        won't do this, `initialize` function will fail. Check if current is set using
        `max_current_set`, read it using `max_current` or set with `set_max_current`
        function. Since ACS712 have only three ranges, up to 5A, 20A or 30A, enumeration
        is used to represent those values.

    Usage:
        Read the current using `read` function. It will return amount of current in
        amps or milliamps which is being measured by sensor.

        To set the unit, use `set_unit` function, which accepts `ACS712::Unit` enum value.
        By default, it's ACS712::Unit::Amps
*/

#pragma once
#include <stdint.h>
#include <Arduino.h>

class ACS712 {
    // This constans indicates analogRead max value. Change it to 4096 when dealing with
    // Arduino Due or similar boards, which have 12-bit ADC.
    constexpr static double ADC_MAX_VALUE{1024.};
public:

    // Integer values in this enum indicate
    // conversion multiplicators.
    // By default, value is calculated in millivolts
    enum class Unit : unsigned {
        Amps = 1, Milliamps = 1000
    };

    // Integer values in this enum indicate
    // millivolts per amp for given sensor range
    enum class MaxCurrent : unsigned {
        Max5A = 185,
        Max20A = 100,
        Max30A = 66
    };

    // C-tors and initialization
    ACS712() = default;
    ACS712(uint8_t vout_pin, MaxCurrent max_current, bool init = true);

    // Initializes the object and Arduino peripherals.
    // Returns false, if initialization failed.
    bool initialize();

    // Sets pins used by object
    void set_pins(uint8_t vout_pin);

    // Sets max current sensor can read
    void set_max_current(MaxCurrent max_current);

    // Returns max current which sensor can read
    MaxCurrent max_current() const;
    
    // Set current unit for `read` function
    void set_unit(Unit unit);

    // Returns the current unit that the function returns
    Unit unit() const;

    bool max_current_set() const;
    bool initialized() const;
    bool pins_set() const;

    // Actual functionality

    // Reads the current draw measured by sensor.
    // In case of error (e.g. object is not initialized), it will always return 0.
    // DO NOT FORGET to call `initialize` if you constructed the object
    // with non-default c-tor and did not initialized it manually BEFORE
    // calling this function.
    double read() const;


private:    
    // Helper function converting raw analogRead value to millivolts.
    template <typename T>
    T raw_value_to_millivolts(T raw_value) const {
        return static_cast<T>((static_cast<double>(raw_value) * 5.0) / ADC_MAX_VALUE);
    }

    uint8_t m_vout_pin{};

    bool m_initialized{false};
    bool m_pin_set{false};
    bool m_max_current_set{false};

    Unit m_amp_unit{Unit::Milliamps};
    MaxCurrent m_max_current{};
};
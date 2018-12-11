#include "acs712.hpp"

ACS712::ACS712(uint8_t vout_pin, ACS712::MaxCurrent max_current, bool init) {
    set_pins(vout_pin);
    set_max_current(max_current);
    if (init) initialize();
}

bool ACS712::initialize() {
    if (initialized()) { return true; }
    if (!max_current_set()) { return false; }
    if (!pins_set()) { return false; }

    pinMode(INPUT, m_vout_pin);
    m_initialized = true;
    return true;
}

void ACS712::set_pins(uint8_t vout_pin) {
    m_vout_pin = vout_pin;
    m_pin_set = true;
}

void ACS712::set_max_current(MaxCurrent max_current) {
    m_max_current = max_current;
    m_max_current_set = true;
}

ACS712::MaxCurrent ACS712::max_current() const {
    return m_max_current;
}

void ACS712::set_unit(ACS712::Unit unit)  {
    m_amp_unit = unit;
}

ACS712::Unit ACS712::unit() const {
    return m_amp_unit;
}

bool ACS712::max_current_set() const {
    return m_max_current_set;
}

bool ACS712::initialized() const {
    return m_initialized;
}

bool ACS712::pins_set() const {
    return m_pin_set;
}

double ACS712::read() const {
    auto raw_value = static_cast<unsigned>(analogRead(m_vout_pin));
    auto millivolts = raw_value_to_millivolts<double>(raw_value);

    auto amps = millivolts / static_cast<double>(m_max_current);
    return amps * static_cast<double>(m_amp_unit);
}


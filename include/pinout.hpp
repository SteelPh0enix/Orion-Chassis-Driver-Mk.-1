#pragma once
#include <stdint.h>
#include <Arduino.h>

namespace Pinout {
    constexpr uint8_t PWM_1 = 2;
    constexpr uint8_t PWM_2 = 3;
    constexpr uint8_t PWM_3 = 4;
    constexpr uint8_t PWM_4 = 5;

    constexpr uint8_t DIR_1A = 24;
    constexpr uint8_t DIR_1B = 25;
    constexpr uint8_t DIR_2A = 26;
    constexpr uint8_t DIR_2B = 27;
    constexpr uint8_t DIR_3A = 28;
    constexpr uint8_t DIR_3B = 29;
    constexpr uint8_t DIR_4A = 30;
    constexpr uint8_t DIR_4B = 31;

    constexpr uint8_t CURRENT_1 = A1;
    constexpr uint8_t CURRENT_2 = A3;
    constexpr uint8_t CURRENT_3 = A5;
    constexpr uint8_t CURRENT_4 = A7;

    constexpr uint8_t TEMPERATURE_1 = A0;
    constexpr uint8_t TEMPERATURE_2 = A2;
    constexpr uint8_t TEMPERATURE_3 = A4;
    constexpr uint8_t TEMPERATURE_4 = A6;

    constexpr uint8_t JOYSTICK_X = A8;
    constexpr uint8_t JOYSTICK_Y = A9;
    constexpr uint8_t JOYSTICK_BACK_BUTTON = 32;
}
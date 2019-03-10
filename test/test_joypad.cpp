#include <Arduino.h>
#include <button.hpp>
#include <joypad.hpp>
#include <pinout.hpp>

Joypad joy;
Button joyButton;
Button joyBackButton;

void setup() {
  joy.set_pins(Pinout::JOYSTICK_X, Pinout::JOYSTICK_Y);
  joyButton.set_pins(Pinout::JOYSTICK_BUTTON);
  joyBackButton.set_pins(Pinout::JOYPAD_BACK_BUTTON);

  joy.initialize();
  joyButton.initialize();
  joyBackButton.initialize();

  joy.calibrate();
  joy.invert_x(true);

  Serial.begin(115200);
}

void loop() {
  joyButton.do_if_pressed([]() { Serial.println("Joystick button pressed"); },
                          false);
  joyBackButton.do_if_pressed(
      []() { Serial.println("Joystick back button pressed"); }, false);

  auto joyData = joy.read();
  Serial.print("X: ");
  Serial.print(joyData.x);
  Serial.print(", Y: ");
  Serial.println(joyData.y);

  delay(100);
}
#include <Arduino.h>
#include <chassis.hpp>
#include <joypad.hpp>
#include <pinout.hpp>

void print_wheel_data(Orion::Wheel::Feedback const& feedback,
                      const char* wheel_name) {
  Serial.print(wheel_name);
  Serial.print(":\nSpeed: ");
  Serial.print(feedback.speed);
  Serial.print("\nCurrent: ");
  Serial.print(feedback.current);
  Serial.print("\nTemperature: ");
  Serial.println(feedback.temperature);
}

void print_chassis_data(Orion::Chassis const& chassis) {
  Serial.print("Chassis data:\n");
  Serial.print("Speed: ");
  Serial.print(chassis.speed());
  Serial.print("\nRotation: ");
  Serial.print(chassis.rotation());
  Serial.println('\n');

  const auto feedback = chassis.wheels_feedback();
  print_wheel_data(feedback.left_front, "left front");
  Serial.println();
  print_wheel_data(feedback.right_front, "right front");
  Serial.println();
  print_wheel_data(feedback.left_rear, "left rear");
  Serial.println();
  print_wheel_data(feedback.right_rear, "right rear");
  Serial.println();
  Serial.println();
}

Orion::Chassis chassis;
Joypad joypad;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  joypad.set_pins(Pinout::JOYSTICK_X, Pinout::JOYSTICK_Y);

  chassis.initialize();
  joypad.initialize();

  Serial.print("Is joypad initialized: ");
  Serial.println(joypad.initialized() ? "Yes" : "No");

  Serial.println("Starting main loop...");
}

void loop() {
  const auto joy_data = joypad.read();
  chassis.drive(joy_data.x, joy_data.y);
  print_chassis_data(chassis);
  delay(500);
}

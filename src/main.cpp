#include <Arduino.h>
#include <chassis.hpp>
#include <joystick.hpp>
#include <pinout.hpp>

void print_wheel_data(Orion::Wheel::Feedback const& feedback, const char* wheel_name) {
  Serial.write(wheel_name);
  Serial.write(":\nSpeed: ");
  Serial.write(feedback.speed);
  Serial.write("\nCurrent: ");
  Serial.print(feedback.current);
  Serial.write("\nTemperature: ");
  Serial.println(feedback.temperature);
}

void print_chassis_data(Orion::Chassis const& chassis) {
  Serial.write("Chassis data:\n");
  Serial.write("Speed: ");
  Serial.write(chassis.speed());
  Serial.write("\nRotation: ");
  Serial.write(chassis.rotation());
  Serial.println();

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
Orion::Joystick joystick;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  
  joystick.set_pins(Pinout::JOYSTICK_X, Pinout::JOYSTICK_Y);

  chassis.initialize();
  joystick.initialize();

  Serial.print("Is joystick initialized: ");
  Serial.println(joystick.initialized() ? "Yes" : "No");

  Serial.println("Starting main loop...");
}

void loop() {
  const auto joy_data = joystick.read();
  chassis.drive(joy_data.x, joy_data.y);
  print_chassis_data(chassis);  
}

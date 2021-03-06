# ACS712 analog current sensor

## Description
This class allows to easely use ACS712 current sensor.
    
## Initialization

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

## Usage

Read the current using `read` function. It will return amount of current in
amps or milliamps which is being measured by sensor.

To set the unit, use `set_unit` function, which accepts `ACS712::Unit` enum value.
By default, it's `ACS712::Unit::Amps`

## Example

```cpp
#include <Arduino.h>
#include <acs712.hpp>

ACS712 current_sensor;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing ACS712...");
  current_sensor.set_max_current(ACS712::MaxCurrent::Max20A);
  current_sensor.set_pins(A0);
  Serial.print("Initialized? ");
  Serial.println(current_sensor.initialize() ? "Yes" : "No");

  // You can change current unit using `set_unit` function
  // current_sensor.set_unit(ACS712::Unit::Milliamps);
}

void loop() {
  Serial.print("Readed current: ");
  Serial.print(current_sensor.read());
  Serial.println("A");
  delay(500);
}
```
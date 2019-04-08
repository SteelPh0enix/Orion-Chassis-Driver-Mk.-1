#pragma once

struct ChassisDataInput {
  int left_front_speed;
  int right_front_speed;
  int left_rear_speed;
  int right_rear_speed;
};

class DataInput {
 public:
    virtual ChassisDataInput data() const = 0;
    virtual bool readData() = 0;
};
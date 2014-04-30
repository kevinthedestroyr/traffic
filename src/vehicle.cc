#include "vehicle.h"
#include <iostream>

Vehicle::Vehicle(const float& velocity)
    : position_(Point(0,0)), velocity_(velocity),
      acceleration_(kDefaultAcceleration), length_(kDefaultLength),
      width_(kDefaultWidth), rotation_(kDefaultRotation),
      max_velocity_(kDefaultMaxVelocity), driver_(this) {
}
    

Vehicle::Vehicle(
    const Point& position,
    const float& velocity,
    const float& acceleration,
    const float& rotation,
    const float& length,
    const float& width,
    const float& max_velocity)
    : position_(position), velocity_(velocity), acceleration_(acceleration),
      length_(length), width_(width), rotation_(rotation),
      max_velocity_(max_velocity), driver_(this) {

}

Vehicle::Vehicle(
    const Point& position,
    const float& velocity,
    const float& rotation)
    : position_(position), velocity_(velocity),
      acceleration_(kDefaultAcceleration), length_(kDefaultLength),
      width_(kDefaultWidth), rotation_(rotation),
      max_velocity_(kDefaultMaxVelocity), driver_(this) {

}

void Vehicle::Step(const float& interval) {
  float x_new = (velocity_*cos(rotation_)*interval) +
      (0.5*acceleration_*cos(rotation_)*pow(interval, 2));	
  float y_new = (velocity_*sin(rotation_)*interval) +
      (0.5*acceleration_*sin(rotation_)*pow(interval, 2));	
  position_ += Point(x_new, y_new);

  float velocity_new = acceleration_*interval + velocity_;
  if (velocity_new <= max_velocity_) {
      velocity_ = velocity_new;
  }

  /* TODO check validity of driver acceleration */
  driver_.Update();
  float driver_acceleration = driver_.desired_acceleration();
  if (driver_acceleration > 0) {
    acceleration_ = driver_acceleration < kDefaultMaxAcceleration
                    ? driver_acceleration
                    : kDefaultMaxAcceleration;
  } else {  /* slowing down */
    acceleration_ = driver_acceleration > kDefaultMaxDeceleration
                    ? driver_acceleration
                    : kDefaultMaxDeceleration;
  }
}

void Vehicle::SetDriversRoad(const Road* rp) {
  driver_.SetRoad(rp);
}

void Vehicle::Turn(const float& theta) {
  /* TODO accurate turning radius */
  /* TODO limits on turning */
  rotation_ += theta;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v) {
  os << v.position_;
  return os;
}


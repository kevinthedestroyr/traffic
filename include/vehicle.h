#ifndef VEHICLE_H
#define VEHICLE_H

#include "point.h"
#include "driver.h"
#include <cmath>
#include <iostream>

/*
 * Class containing parameters and methods relating to the physical vehicle.
 * All units in meters.
 */
class Vehicle {
  public:
    Vehicle(const Point& p,
            const float& v,
            const float& rotation);
    Vehicle(const Point& p,
            const float& v,
            const float& a,
            const float& rotation,
            const float& length,
            const float& width,
            const float& max_velocity);

    float velocity() const;
    float max_velocity() const;

    void Step(const float& interval);
    bool Collision(const Point& other) const;
    void SetDriversRoad(const Road* rp);
    void Turn(const float& ang);

    Point position() const;

    friend std::ostream&
        operator<<(std::ostream& os, const Vehicle& v);

  private:
    /* disallow copy and assign */
    Vehicle(const Vehicle&);
    Vehicle operator=(const Vehicle&);

    static constexpr float kDefaultAcceleration = 0;
    static constexpr float kDefaultLength = 1;
    static constexpr float kDefaultWidth = 1;
    static constexpr float kDefaultMaxVelocity = 54.0;
    Point position_;
    float velocity_;      /* velocity in m/s (direction determined by rotation */
    float acceleration_;  /* acceleration in m/s^2 (direction determined by rotation */
    float length_;
    float width_;
    float rotation_;      /* radians - relative to positive x axis */
    const float max_velocity_;  /* m/s */
    Driver driver_;
};

inline float Vehicle::velocity() const {
  return velocity_;
}

inline float Vehicle::max_velocity() const {
  return max_velocity_;
}

inline Point Vehicle::position() const {
  return position_;
}

#endif  // VEHICLE_H

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
    /* public class constants */
    static constexpr float kDefaultLength = 4.2;
    
    /* constructors and destructors */
    Vehicle(const float& v);
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

    /* public member functions*/
    void Step(const float& interval);
    bool Collision(const Point& other) const;
    void SetDriversRoad(const Road* rp);
    void Turn(const float& ang);

    /* accessors and modifiers*/
    float velocity() const;
    float max_velocity() const;
    Point position() const;         
    void position(const Point& p);
    float rotation() const;
    void rotation(const float& r);
    float length() const;
    float width() const;

    friend std::ostream&
        operator<<(std::ostream& os, const Vehicle& v);

  private:
    /* disallow copy and assign */
    Vehicle(const Vehicle&);
    Vehicle operator=(const Vehicle&);

    /* private class constants */
    static constexpr float kDefaultAcceleration = 0;
    static constexpr float kDefaultRotation = 0;
    static constexpr float kDefaultWidth = 1.83;
    static constexpr float kDefaultMaxVelocity = 54.0;
    static constexpr float kDefaultMaxAcceleration = 10;  /* m/s/s - engine power / weight */
    static constexpr float kDefaultMaxDeceleration = -10; /* m/s/s - braking power / weight */
    Point position_;
    float velocity_;            /* velocity in m/s (direction determined by rotation */
    float acceleration_;        /* acceleration in m/s^2 (direction determined by rotation */
    float length_;
    float width_;
    float rotation_;            /* radians - relative to positive x axis */
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

inline void Vehicle::position(const Point& p) {
  position_ = p;
}

inline float Vehicle::rotation() const {
  return rotation_;
}
inline void Vehicle::rotation(const float& r) {
  rotation_ = r;
}

inline float Vehicle::length() const {
  return length_;
}

inline float Vehicle::width() const {
  return width_;
}

#endif  // VEHICLE_H

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

    /*
     * Steps the vehicle's position based on the time
     * given by interval (in seconds).
     */
    void Step(const float& interval);

    /*
     * Checks if the position indicated by arguments 
     * is inside the bounds of this vehicle.
     * Return true if it is.
     */
    bool Collision(const Point& other) const;

    /*
     * Passes road reference to driver so he can
     * see the vehicles around him.
     */
    void SetDriversRoad(const Road* rp);

    /* Return corner positions, taking rotation into account */
    Point topright() const; 
    Point bottomright() const; 
    Point topleft() const; 
    Point bottomleft() const; 

    /* Turns the vehicle by argument given in radians. */
    void Turn(const float& ang);

    friend std::ostream&
        operator<<(std::ostream& os, const Vehicle& v);

  private:
    /* disallow copy and assign */
    Vehicle(const Vehicle&);
    Vehicle operator=(const Vehicle&);

    static const float kDefaultAcceleration = 0;
    static const float kDefaultLength = 1;
    static const float kDefaultWidth = 1;
    static const float kDefaultMaxVelocity = 54.0;
    Point position_;
    float velocity_;      /* velocity in m/s (direction determined by rotation */
    float acceleration_;  /* acceleration in m/s^2 (direction determined by rotation */
    float length_;
    float width_;
    float rotation_;      /* radians - relative to positive x axis */
    float max_velocity_;  /* m/s */
    Driver driver_;
};

#endif  // VEHICLE_H

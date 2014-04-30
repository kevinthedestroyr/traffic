#ifndef DRIVER_H
#define DRIVER_H

#include <vector>
#include <cstdlib>

class Vehicle;
class Road;

class Driver {
  public:
    Driver(Vehicle* const my_vehicle,
           const float& following_factor,
           const float& speed_offset,
           const float& slow_down_factor);
    Driver(Vehicle* const my_vehicle);
    void Update();
    void SetRoad(const Road* rp);

    float desired_acceleration() const;
    float following_factor() const;
    void following_factor(const float& f);
    float speed_offset() const;
    void speed_offset(const float& s);
    float slow_down_factor() const;

  private:
    /* dissallow copy and assign */
    Driver(const Driver&);
    void operator=(const Driver&);

    static constexpr float kDefaultFollowingFactor = 10;
    static constexpr float kDefaultSpeedOffset = 0;
    static constexpr float kDefaultSlowDownFactor = 100;
    Vehicle* const vehicle_;                /* Pointer to this drivers vehicle */
    const float following_factor_;          /* speed*(average vehicle length) / (following factor) -> desired following distance */
    const float speed_offset_;              /* add to speed limit for desired speed */
    const float slow_down_factor_;          /* this times percent difference in following distance and desired following distance gives desired decceleration */
    float desired_acceleration_;            /* is the driver hitting the gas or break */
    float desired_turn_;                    /* is the driver turning */
    std::vector<Vehicle*> close_vehicles_;  /* vehicles driver is aware of (think vision) */
    const Road* road_;                      /* pointer to the road this driver is on */

    void UpdateDesiredAcceleration();       /* update desired accel based on other vehicles */
    void UpdateDesiredTurn();               /* update desired turn based on road */
};

inline void Driver::Update() {
  UpdateDesiredAcceleration();
  UpdateDesiredTurn();
}

inline void Driver::SetRoad(const Road* rp) {
  road_ = rp;
}

inline float Driver::desired_acceleration() const {
  return desired_acceleration_;
}

inline float Driver::following_factor() const {
  return following_factor_;
}

inline float Driver::speed_offset() const {
  return speed_offset_;
}

inline float Driver::slow_down_factor() const {
  return slow_down_factor_;
}

#endif // DRIVER_H

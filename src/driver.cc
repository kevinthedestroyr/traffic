#include "driver.h"
#include "vehicle.h"
#include "road.h"
#include "common.h"

Driver::Driver(Vehicle* const my_vehicle,
               const float& following_factor,
               const float& speed_offset,
               const float& slow_down_factor)
    : vehicle_(my_vehicle),
    following_factor_(following_factor),
    speed_offset_(speed_offset),
    slow_down_factor_(slow_down_factor),
    road_(NULL) {
  
}

Driver::Driver(Vehicle* const my_vehicle)
    : vehicle_(my_vehicle),
    following_factor_(kDefaultFollowingFactor),
    speed_offset_(kDefaultSpeedOffset),
    slow_down_factor_(kDefaultSlowDownFactor),
    road_(NULL) {

}

void Driver::UpdateDesiredAcceleration() {
  /* driver not associated with road yet */
  if (!road_) {  
    desired_acceleration_ = 0;
    return;
  }
  /* TODO realistic accelerations */
  /* iterate through other vehicles and see if driver needs to slow down */
  std::vector<Vehicle*> vehicles = road_->GetVehicles();
  for (const auto& vp : vehicles) {
    /* only look at cars in front of you */
    if (vp == vehicle_ || vp->position().x() < vehicle_->position().x()) {
        continue;
    }
    /* TODO account for rotation of vehicle here */
    float other_vehicle_tail = vp->position().x() - vp->length()/2.0f;
    float vehicle_head = vehicle_->position().x() + vehicle_->length()/2.0f; 
    float preferred_following_distance = vehicle_->velocity()
                                         * Vehicle::kDefaultLength
                                         / following_factor_; 
    float following_distance = other_vehicle_tail - vehicle_head;
    if (following_distance < preferred_following_distance) {
        if (vehicle_->velocity() > 0) {
            desired_acceleration_ = -1 * ((preferred_following_distance-following_distance)
                                    / preferred_following_distance)
                                    * slow_down_factor_;
        }
        else {
            desired_acceleration_ = 0;
        }
        return;
    }
  }
  if (vehicle_->velocity() < road_->speed_limit()+speed_offset_) {
    desired_acceleration_ = 1;
    return;
  }
  if (vehicle_->velocity() > road_->speed_limit()+speed_offset_) {
    if (vehicle_->velocity() > 0) {
       desired_acceleration_ = -1;
    }
    else {
       desired_acceleration_ = 0;
    }
    return;
  }
}

void Driver::UpdateDesiredTurn() {
  /* TODO this should be based on desire to change lane */
  desired_turn_ = 0;
}

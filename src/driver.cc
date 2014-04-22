#include "driver.h"
#include "vehicle.h"
#include "road.h"

Driver::Driver(Vehicle* const my_vehicle,
               const float& following_factor,
               const float& speed_offset)
    : vehicle_(my_vehicle),
    following_factor_(following_factor),
    speed_offset_(speed_offset), road_(NULL) {
  
}

Driver::Driver(Vehicle* const my_vehicle)
    : vehicle_(my_vehicle),
    following_factor_(kDefaultFollowingFactor),
    speed_offset_(kDefaultSpeedOffset) {

}

void Driver::UpdateDesiredAcceleration() {
  /* driver not associated with road yet */
  if (!road_) {  
    desired_acceleration_ = 0;
    return;
  }
  /* TODO base acceleration on other cars on the road */
  /* TODO realistic accelerations */
  if (vehicle_->velocity() < road_->speed_limit()+speed_offset_) {
    desired_acceleration_ = 1;
    return;
  }
  if (vehicle_->velocity() > road_->speed_limit()+speed_offset_) {
    desired_acceleration_ = -1;
    return;
  }
}

void Driver::UpdateDesiredTurn() {
  /* TODO this should be based on desire to change lane */
  desired_turn_ = 0;
}

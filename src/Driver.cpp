#include "Driver.h"
#include "Vehicle.h"
#include "Road.h"

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

/* TODO Implement this. For now, hold the course */
void Driver::UpdateDesiredAcceleration() {
  desired_acceleration_ = 0;
}

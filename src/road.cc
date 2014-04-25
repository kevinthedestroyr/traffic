#include "road.h"
#include "vehicle.h"

Road::Road()
    : num_lanes_(kDefaultNumLanes), lane_width_(kDefaultLaneWidth),
      shoulder_width_(kDefaultShoulderWidth), speed_limit_(kDefaultSpeedLimit),
      length_(kDefaultLength) {

}

void Road::Step(const float& interval) {
  std::vector<Vehicle*> vehicles_to_delete;
  for (std::vector<Vehicle*>::iterator it = vehicles_.begin();
       it != vehicles_.end(); ++it) {
    (*it)->Step(interval);
    Point p = (*it)->position();
    if (p.x() > length_) {
      vehicles_to_delete.push_back(*it);
    }
  }
  for (auto vp : vehicles_to_delete) {
    RemoveVehicle(vp);
  }
}

void Road::AddVehicle(Vehicle* vp) {
  vp->SetDriversRoad(this);
  vehicles_.push_back(vp);
}

void Road::RemoveVehicle(Vehicle* vp) {
  std::cout << "Removing Vehicle!!!" << std::endl;
  for (std::vector<Vehicle*>::iterator it = vehicles_.begin();
       it != vehicles_.end(); ++it) {
    if (*it == vp) {
      vehicles_.erase(it);
      return;
    }
  }
}

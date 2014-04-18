#include "road.h"
#include "vehicle.h"

Road::Road()
    : kNumLanes_(kDefaultNumLanes), kLaneWidth_(kDefaultLaneWidth),
      kShoulderWidth_(kDefaultShoulderWidth) {

}

void Road::Step(const float& interval) {
  for (std::vector<Vehicle*>::iterator it = vehicles_.begin();
       it != vehicles_.end(); ++it) {
    (*it)->Step(interval);
  }
}

void Road::AddVehicle(Vehicle* vp) {
  vp->SetDriversRoad(this);
  vehicles_.push_back(vp);
}

void Road::RemoveVehicle(Vehicle* vp) {
  for (std::vector<Vehicle*>::iterator it = vehicles_.begin();
       it != vehicles_.end(); ++it) {
    if (*it == vp) {
      vehicles_.erase(it);
      return;
    }
  }
}

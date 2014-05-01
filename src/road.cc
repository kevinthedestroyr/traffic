#include "road.h"
#include "vehicle.h"
#include <algorithm>
#include <cmath>

Road::Road()
    : num_lanes_(kDefaultNumLanes), lane_width_(kDefaultLaneWidth),
      shoulder_width_(kDefaultShoulderWidth), speed_limit_(kDefaultSpeedLimit),
      length_(kDefaultLength) {
  for (int i = 0; i < num_lanes_; i++) {
    float lane_center = shoulder_width_
                        + static_cast<float>(i)*lane_width_
                        + 0.5 * lane_width_;
    lane_centers_.push_back(lane_center);
  }
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

bool Road::AddVehicle(Vehicle* vp, const unsigned& lane) {
  if (lane < 0 || lane >= lane_centers_.size()) {
    std::cerr << "ERROR: ";
    std::cerr << "Could not add vehicle becuase lane ";
    std::cerr << lane << " does not correspond to a lane on this road (";
    std::cerr << lane_centers_.size() << " lanes)" << std::endl;
    return false;
  }
  vp->position(Point(vp->position().x(), lane_centers_.at(lane)));
  vp->SetDriversRoad(this);
  vehicles_.push_back(vp);
  return true;
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

int Road::GetCurrentLane(const Vehicle* vp) const {
  std::vector<float> distances(lane_centers_);
  for (auto& distance : distances) {
    distance = abs(distance - vp->position().y());
  }
  std::vector<float>::iterator min_element = std::min_element(distances.begin(), distances.end());
  std::cout << "lane: " << min_element-distances.begin() << std::endl;
  return min_element - distances.begin();
}

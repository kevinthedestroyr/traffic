#include "common.h"
#include <vector>

class Vehicle;

class Road {
  public:
    /* constructors */
    Road();

    /* public functions */
    void Step(const float& interval);                    /* steps all vehicles on road to next state */
    bool AddVehicle(Vehicle* vp, const unsigned& lane);  /* adds a vehicle to lane on road, return true if successful, false otherwise */
    void RemoveVehicle(Vehicle* vp);                     /* removes vehicle from road */
    int NumVehicles() const;                             /* returns number of vehicles currently on road */
    std::vector<Vehicle*> GetVehicles() const;           /* returns copy of vehicles data */
    int GetCurrentLane(const Vehicle*) const;           /* returns the lane of the given vehicle on road */

    float speed_limit() const;
    float length() const;
  private:
    /* disallow copy and assign */
    Road(const Road&);
    Road operator=(const Road&);

    /* private default values */
    static constexpr int kDefaultNumLanes = 2;         /* meters */
    static constexpr float kDefaultLaneWidth = 2.7;    /* meters, average highway lane */
    static constexpr float kDefaultShoulderWidth = 1;  /* meters */
    static constexpr float kDefaultSpeedLimit = kMPSOverMPH * 65;
    static constexpr float kDefaultLength = 500;

    /* private variables */
    std::vector<Vehicle*> vehicles_;  /* pointers to Vehicles on this road */
    const int num_lanes_;             /* In one direction. Only one-way supported */
    const float lane_width_;
    const float shoulder_width_;
    const float speed_limit_;         /* m/s (for consistency) */
    const float length_;              /* meters */
    std::vector<float> lane_centers_;
};

inline int Road::NumVehicles() const {
  return vehicles_.size();
}

inline float Road::speed_limit() const {
  return speed_limit_;
}

inline std::vector<Vehicle*> Road::GetVehicles() const {
  return vehicles_;
}

inline float Road::length() const {
  return length_;
}

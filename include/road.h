#include <vector>

namespace {
constexpr float kMPSOverMPH = 0.44704;
constexpr float kMetersPerMile = 1609.34;
}

class Vehicle;

class Road {
  public:
    /* constructors */
    Road();

    /* public functions */
    void Step(const float& interval);    /* steps all vehicles on road to next state */
    void AddVehicle(Vehicle* vp);        /* adds a vehicle to the road */
    void RemoveVehicle(Vehicle* vp);     /* removes vehicle from road */
    int NumVehicles() const;  /* returns number of vehicles currently on road */

    float speed_limit() const;
  private:
    /* disallow copy and assign */
    Road(const Road&);
    Road operator=(const Road&);

    /* private default values */
    static constexpr int kDefaultNumLanes = 2;         /* meters */
    static constexpr float kDefaultLaneWidth = 2.7;    /* meters, average highway lane */
    static constexpr float kDefaultShoulderWidth = 1;  /* meters */
    static constexpr float kDefaultSpeedLimit = kMPSOverMPH * 65;
    static constexpr float kDefaultLength = 1 * kMetersPerMile;

    /* private variables */
    std::vector<Vehicle*> vehicles_;  /* pointers to Vehicles on this road */
    const int num_lanes_;             /* In one direction. Only one-way supported */
    const float lane_width_;
    const float shoulder_width_;
    const float speed_limit_;         /* m/s (for consistency) */
    const float length_;              /* meters */
};

inline int Road::NumVehicles() const {
  return vehicles_.size();
}

inline float Road::speed_limit() const {
  return speed_limit_;
}

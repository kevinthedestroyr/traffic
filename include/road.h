#include <vector>

/* Following needs to be a define to use with constants (at least until C++11). */
#define MPS_OVER_MPH 0.44704

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
    static const int kDefaultNumLanes = 2;         /* meters */
    static const float kDefaultLaneWidth = 2.7;    /* meters, average highway lane */
    static const float kDefaultShoulderWidth = 1;  /* meters */
    static const float kDefaultSpeedLimit = MPS_OVER_MPH * 65;

    /* private variables */
    std::vector<Vehicle*> vehicles_;  /* pointers to Vehicles on this road */
    const int num_lanes_;             /* In one direction. Only one-way supported */
    const float lane_width_;
    const float shoulder_width_;
    const float speed_limit_;         /* m/s (for consistency) */
};

inline int Road::NumVehicles() const {
  return vehicles_.size();
}

inline float Road::speed_limit() const {
  return speed_limit_;
}

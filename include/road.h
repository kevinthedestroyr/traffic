#include <vector>

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
  private:
    /* disallow copy and assign */
    Road(const Road&);
    Road operator=(const Road&);

    /* private default values */
    static const int kDefaultNumLanes = 2;         /* meters */
    static const float kDefaultLaneWidth = 2.7;    /* meters, average highway lane */
    static const float kDefaultShoulderWidth = 1;  /* meters */

    /* private variables */
    std::vector<Vehicle*> vehicles_;  /* pointers to Vehicles on this road */
    const int num_lanes_;              /* In one direction. Only one-way supported */
    const float lane_width_;
    const float shoulder_width_;
};

inline int Road::NumVehicles() const {
  return vehicles_.size();
}

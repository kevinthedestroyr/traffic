#include "point.h"
#include "vehicle.h"
#include "road.h"
#include "display.h"
#include <iostream>
#include <cmath>
#include <ctime>

namespace {
constexpr float PI = 3.14159265359;
}

int main(int argc, char* argv[]) {
  Vehicle v1(Point(0, 0), 1, 0);
  Vehicle v2(Point(2, 0), 1, 0);
  Road road;
  road.AddVehicle(&v1);
  road.AddVehicle(&v2);
  Display d(road);
  bool started = d.Start();
  if (!started) {
    std::cerr << "Failed to initialize SDL window" << std::endl;
    return -1;
  }
  road.Step(1);
  for (Road::VehicleIterator it = road.VehicleIteratorBegin();
       it != road.VehicleIteratorEnd();
       it++) {
    std::cout << **it << std::endl;
  }
  usleep(2e6);
  d.Stop();
}

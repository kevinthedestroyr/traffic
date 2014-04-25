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
  Vehicle v2(Point(0, 0), 10, 0);
  Vehicle v1(Point(10, 3), 0, 0);
  Road road;
  road.AddVehicle(&v1);
  road.AddVehicle(&v2);
  Display d(road);
  bool started = d.Initialize();
  if (!started) {
    std::cerr << "Failed to initialize SDL window" << std::endl;
    return -1;
  }
  for (int i = 0; i < 4000; ++i) {
    d.Update();
    road.Step(0.01);
    usleep(1e3);
  }
}

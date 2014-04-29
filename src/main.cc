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
  Road road;
  Display d(road);
  bool started = d.Initialize();
  if (!started) {
    std::cerr << "Failed to initialize SDL window" << std::endl;
    return -1;
  }
  for (int i = 0; i < 5000; ++i) {
    if (i % 100 == 0) {
      road.AddVehicle(new Vehicle(Point(0,0), 10, 0));
    }
    d.Update();
    road.Step(0.01);
    if (road.NumVehicles() <= 0) {
      break;
    }
    usleep(1e3);
  }
}

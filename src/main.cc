#include "point.h"
#include "vehicle.h"
#include "road.h"
#include "display.h"
#include <iostream>
#include <cmath>

namespace {
  const float PI = 3.14159265359;
}

int main(int argc, char* argv[]) {
  Vehicle v1(Point(0, 0), 1, 0);
  Vehicle v2(Point(2, 0), 1, 0);
  Road road;
  road.AddVehicle(&v1);
  road.AddVehicle(&v2);
  Display d(road);
  if (!d.initialized()) {
    std::cerr << "Failed to initialize SDL window" << std::endl;
    return -1;
  }
  SDL_Delay(3000);
  road.Step(1);
}

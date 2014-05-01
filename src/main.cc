#include "point.h"
#include "vehicle.h"
#include "road.h"
#include "display.h"
#include <iostream>
#include <cmath>
#include <ctime>

int main(int argc, char* argv[]) {
  Road road;
  Display d(road);
  bool started = d.Initialize();
  if (!started) {
    std::cerr << "Failed to initialize SDL window" << std::endl;
    return -1;
  }
  for (int i = 0; i < 5000; ++i) {
    if (i == 0) {
      road.AddVehicle(new Vehicle(1), 0);
      road.AddVehicle(new Vehicle(5), 1);
    }
    if (i == 1200) {
        road.AddVehicle(new Vehicle(30), 0);
        road.AddVehicle(new Vehicle(40), 1);
    }
    d.Update();
    road.Step(0.01);
    if (road.NumVehicles() <= 0) {
      break;
    }
    usleep(1e3);
  }
}

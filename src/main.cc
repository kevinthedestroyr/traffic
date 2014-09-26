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
  SDL_Event e;
  bool quit = false;
  /* wait for click to start */
  while(1) {
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
      quit = true;
      break;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN) {
      break;
    }
    usleep(1e4);
  }
  /* main loop */
  for (int i = 0; !quit; ++i) {
    SDL_PollEvent(&e);
    if (e.type == SDL_QUIT) {
      break;
    }
    if (i == 0) {
      road.AddVehicle(new Vehicle(0), 0);
      road.AddVehicle(new Vehicle(0), 1);
    }
    if (i == 1200) {
      road.AddVehicle(new Vehicle(20), 0);
      road.AddVehicle(new Vehicle(25), 1);
    }
    if (i == 1500) {
      road.AddVehicle(new Vehicle(25), 0);
      road.AddVehicle(new Vehicle(25), 1);
    }
    d.Update();
    road.Step(0.01);
    if (road.NumVehicles() <= 0) {
      break;
    }
    usleep(1e3);
  }
}

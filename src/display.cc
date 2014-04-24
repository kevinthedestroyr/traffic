#include "display.h"
#include "road.h"
#include "vehicle.h"
#include <iostream>
#include <ctime>
#include <cstdint>
#include <vector>

Display::Display(const Road& r,
                 const int& window_width,
                 const int& window_height)
    : road_(r), window_(NULL), surface_(NULL), 
      refresh_rate_(kDefaultRefreshRate),
      window_width_(window_width),
      window_height_(window_height) {
}

Display::Display(const Road& r)
    : road_(r), window_(NULL), surface_(NULL), 
      refresh_rate_(kDefaultRefreshRate),
      window_width_(kDefaultWindowWidth),
      window_height_(kDefaultWindowHeight) {
      
}

Display::~Display() {
  if (surface_) {
    SDL_FreeSurface(surface_);
    surface_ = NULL;
  }
  if (window_) {
    SDL_DestroyWindow(window_);
    window_ = NULL;
  }
  SDL_Quit();
}

bool Display::Initialize() {
  /* init SDL */
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  /* create a window_ */
  window_ = SDL_CreateWindow(
      "Traffic",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      window_width_,
      window_height_,
      SDL_WINDOW_SHOWN);
  if (!window_) {
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  /* fill the window_ */
  surface_ = SDL_GetWindowSurface(window_);
  if (!surface_) {
    std::cerr << SDL_GetError() << std::endl;
    return false;
  }
  const SDL_Rect* FILL_ALL = NULL;
 window_color_ = SDL_MapRGB(surface_->format,
                            kDefaultWindowColorR,
                            kDefaultWindowColorG,
                            kDefaultWindowColorB);
  SDL_FillRect(surface_, FILL_ALL, window_color_);
  SDL_UpdateWindowSurface(window_);

  vehicle_color_ = SDL_MapRGB(surface_->format,
                              kDefaultVehicleColorR,
                              kDefaultVehicleColorG,
                              kDefaultVehicleColorB);
  return true;
}

void Display::Update() {
  if (!surface_ || !window_) {
    std::cerr << "ERROR: Cannot start display before initialization." << std::endl;
    return;
  }
  /* clear window */
  SDL_FillRect(surface_, NULL, window_color_);
  /* populate new vehicle positions */
  vehicles_ = road_.GetVehicles();
  for (const auto& vp : vehicles_) {
    int x, y;
    GetVehicleDisplayPosition(*vp, &x, &y);
    SDL_Rect vehicle_rect; 
    vehicle_rect.x = x;
    vehicle_rect.y = y;
    vehicle_rect.w = 10;
    vehicle_rect.h = 10;
    SDL_FillRect(surface_, &vehicle_rect, vehicle_color_);
  }
  SDL_UpdateWindowSurface(window_);
}


void Display::GetVehicleDisplayPosition(const Vehicle& v, int* x, int* y) {
  Point p = v.position();
  *x = static_cast<int>(p.x());
  *y = static_cast<int>(p.y());
}

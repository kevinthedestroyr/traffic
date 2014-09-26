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
      window_height_(window_height),
      pixels_per_meter_(window_width_ / r.length()) {
}

Display::Display(const Road& r)
    : road_(r), window_(NULL), surface_(NULL), 
      refresh_rate_(kDefaultRefreshRate),
      window_width_(kDefaultWindowWidth),
      window_height_(kDefaultWindowHeight),
      pixels_per_meter_(window_width_ / r.length()) {
  std::cout << "pixels_per_meter_: " << pixels_per_meter_ << std::endl;      
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
    SDL_Rect vehicle_rect;
    GetVehicleDisplayRect(*vp, &vehicle_rect); 
    SDL_FillRect(surface_, &vehicle_rect, vehicle_color_);
  }
  SDL_UpdateWindowSurface(window_);
}


void Display::GetVehicleDisplayRect(const Vehicle& v, SDL_Rect* r) {
  Point p = v.position();
  r->x = static_cast<int>(p.x() * pixels_per_meter_);
  r->y = static_cast<int>(p.y() * pixels_per_meter_) + (window_height_ / 2);
  r->w = (v.length()) * pixels_per_meter_;
  r->h = (v.width()) * pixels_per_meter_;
}

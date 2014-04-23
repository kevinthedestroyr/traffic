#include "display.h"
#include "road.h"
#include <iostream>
#include <ctime>

Display::Display(const Road& r,
                 const int& window_width,
                 const int& window_height)
    : road_(r), window_(NULL), surface_(NULL), 
      refresh_rate_(kDefaultRefreshRate),
      window_width_(window_width),
      window_height_(window_height),
      initialized_(false), quit_(false),
      display_thread_p_(NULL) {
}

Display::Display(const Road& r)
    : road_(r), window_(NULL), surface_(NULL), 
      refresh_rate_(kDefaultRefreshRate),
      window_width_(kDefaultWindowWidth),
      window_height_(kDefaultWindowHeight),
      initialized_(false), quit_(false),
      display_thread_p_(NULL) {
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

void Display::Initialize() {
  /* init SDL */
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << SDL_GetError() << std::endl;
    return;
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
    return;
  }
  /* fill the window_ */
  surface_ = SDL_GetWindowSurface(window_);
  if (!surface_) {
    std::cerr << SDL_GetError() << std::endl;
    return;
  }
  const SDL_Rect* FILL_ALL = NULL;
  SDL_FillRect(surface_, FILL_ALL, SDL_MapRGB(surface_->format, 0, 0, 0));
  SDL_UpdateWindowSurface(window_);
  initialized_ = true;
}

void Display::DisplayLoop() {
  while(!quit_) {
    /* TODO process vehicles and display them */
    usleep(1e6 / static_cast<float>(refresh_rate_));
  }
}

bool Display::Start() {
  if (display_thread_p_) {
    std::cerr << "Display::Start - Display thread already exists. Not starting another.";
    std::cerr << std::endl;
    return false;
  }
  Initialize();
  if (!initialized_) {
    return false;
  }
  display_thread_p_ = new std::thread(&Display::DisplayLoop, this);
  return true;
}

void Display::Stop() {
  quit_ = true;
  if (display_thread_p_) {
    display_thread_p_->join();
    delete display_thread_p_;
    display_thread_p_ = NULL;
  }
}

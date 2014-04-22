#include "display.h"
#include "road.h"
#include <iostream>

Display::Display(const Road& r,
                 const int& window_width,
                 const int& window_height)
    : road_(r), window_(NULL), surface_(NULL), 
      window_width_(window_width),
      window_height_(window_height),
      initialized_(false) {
  Initialize();
}

Display::Display(const Road& r)
    : road_(r), window_(NULL), surface_(NULL), 
      window_width_(kDefaultWindowWidth),
      window_height_(kDefaultWindowHeight),
      initialized_(false) {
  Initialize();
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

/* provide visual display for traffic simulation using SDL library */

#include "SDL2/SDL.h"

class Road;

class Display {
  public:
    Display(const Road& r);
    Display(const Road& r,
            const int& window_width,
            const int& window_height);
    ~Display();
    bool initialized() const;
  private:
    static const int kDefaultWindowWidth = 640;
    static const int kDefaultWindowHeight = 480;

    const Road& road_;
    SDL_Window *window_;
    SDL_Surface *surface_;
    const int window_width_;
    const int window_height_;
    bool initialized_;

    void Initialize();
};

inline bool Display::initialized() const {
  return initialized_;
}

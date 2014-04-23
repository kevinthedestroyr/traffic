/* provide visual display for traffic simulation using SDL library */

#include "SDL2/SDL.h"
#include <thread>

class Road;

class Display {
  public:
    Display(const Road& r);
    Display(const Road& r,
            const int& window_width,
            const int& window_height);
    ~Display();
    bool Start();
    void Stop();
    bool initialized() const;
  private:
    static constexpr int kDefaultWindowWidth = 640;
    static constexpr int kDefaultWindowHeight = 480;
    static constexpr int kDefaultRefreshRate = 30;    /* frames per second */

    const Road& road_;
    SDL_Window *window_;
    SDL_Surface *surface_;
    const int refresh_rate_;  /* frames per second */
    const int window_width_;
    const int window_height_;
    bool initialized_;
    bool quit_;
    std::thread* display_thread_p_;

    void Initialize();
    void DisplayLoop();
};

inline bool Display::initialized() const {
  return initialized_;
}

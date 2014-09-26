/* provide visual display for traffic simulation using SDL library */

#include "SDL2/SDL.h"
#include <cstdint>
#include <vector>

class Road;
class Vehicle;

class Display {
  public:
    Display(const Road& r);
    Display(const Road& r,
            const int& window_width,
            const int& window_height);
    ~Display();
    bool Initialize();
    void Update();
    void GetVehicleDisplayRect(const Vehicle& v, SDL_Rect* vehicle_rect);
  private:
    /* dissallow copy and assign */
    Display(const Display&);
    Display& operator=(const Display&);
    static constexpr int kDefaultWindowWidth = 1280;
    static constexpr int kDefaultWindowHeight = 100;
    static constexpr int kDefaultRefreshRate = 30;    /* frames per second */
    static constexpr int kDefaultWindowColorR = 255;
    static constexpr int kDefaultWindowColorG = 255;
    static constexpr int kDefaultWindowColorB = 255;
    static constexpr int kDefaultVehicleColorR = 0;
    static constexpr int kDefaultVehicleColorG = 0;
    static constexpr int kDefaultVehicleColorB = 0;

    const Road& road_;
    SDL_Window *window_;
    SDL_Surface *surface_;
    uint32_t window_color_;
    uint32_t vehicle_color_;
    const int refresh_rate_;  /* frames per second */
    const int window_width_;
    const int window_height_;
    std::vector<Vehicle*> vehicles_;
    const float pixels_per_meter_;

};


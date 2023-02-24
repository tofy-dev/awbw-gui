#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>

class Entity {
public:
  void setPosition(int x, int y);
  void move(int x_off, int y_off);
private:
  int x_, y_;
};

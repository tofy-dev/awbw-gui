#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

class Unit {
public:
  Unit(std::string country, std::string name, int x, int y, RenderWindow* window);
  void setPosition(int x, int y);
  void move(int x_off, int y_off);

  std::string getName();
  SDL_Texture* getTexture();

private:
  std::string name_;
  int x_, y_;

  SDL_Texture* texture_;
  RenderWindow* window_;
};

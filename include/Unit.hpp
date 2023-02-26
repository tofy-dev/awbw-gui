#pragma once
#include "RenderWindow.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

class Unit {
public:
  static Unit* createUnit(std::string country, std::string name, RenderWindow* window);

  std::string getName();
  std::string getCountry();
  SDL_Texture* getTexture();

  void setName(std::string name) {name_ = name;};
  void setCountry(std::string country) {country_ = country;};
  void setTexture(SDL_Texture* texture) {texture_ = texture;};

private:
  Unit* unit_;

  std::string name_;
  std::string country_;
  SDL_Texture* texture_;
  RenderWindow* window_;
};

#pragma once
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

class Unit {
public:
  Unit(std::string country, std::string name, RenderWindow* window);
  static Unit* createUnit(std::string country, std::string name, RenderWindow* window);

  std::string getName();
  std::string getCountry();
  GIFImage* getGIF();

  void setName(std::string name);
  void setCountry(std::string country);
  void setGIF(std::string path);

  static void setScaling(double scaling);

private:
  std::string name_;
  std::string country_;
  static inline double scaling_ = 1;

  GIFImage gif_;
  RenderWindow* window_;
};

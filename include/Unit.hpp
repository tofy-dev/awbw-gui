#pragma once
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>

#define NATION_AMT 16

class Unit {
public:
  Unit(std::string country, std::string name, RenderWindow* window);
  static Unit* createUnit(std::string country, std::string name, RenderWindow* window);
  static void destroyUnit(Unit*);
  static void setScaling(double scaling);

  std::string getName();
  std::string getCountry();
  GIFImage* getGIF();

  void setName(std::string name);
  void setCountry(std::string country);
  void setGIF(std::string path);

private:
  std::string name_;
  std::string country_;

  GIFImage* gif_;
  RenderWindow* window_;

  static inline double scaling_ = 1;
  static inline std::array<std::string, NATION_AMT> nat_arr_ = {"os", "bm", "ge", "yc", "bh", "rf", "gs", "bd", "ab", "js", "ci", "pc", "tg", "pl", "ar", "wn"};
};

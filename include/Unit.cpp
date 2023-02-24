#include "Unit.hpp"
#include "RenderWindow.hpp"
#include <string>

Unit::Unit() {
  name_ = "";
}

Unit::Unit(std::string country, std::string name, int x, int y, RenderWindow* window) : name_{name}, x_{x}, y_{y}, window_{window}{
  texture_ = window->loadTexture(("res/assets/units/" + country + name + ".gif").c_str());
}

void Unit::setPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

void Unit::move(int x_off, int y_off) {
  x_ += x_off;
  y_ += y_off;
}

std::string Unit::getName() {
  return name_;
}

SDL_Texture* Unit::getTexture() {
  return texture_;
}

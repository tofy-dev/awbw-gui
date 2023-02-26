#include "Unit.hpp"
#include "RenderWindow.hpp"
#include <cstdlib>
#include <string>

Unit* Unit::createUnit(std::string country, std::string name, RenderWindow* window) {
  Unit* unit = (Unit*)SDL_malloc(sizeof(Unit));
  memset(unit, 0, sizeof(Unit));
  unit->unit_ = unit;
  unit->name_ = name;
  unit->country_ = country;
  unit->window_ = window;
  unit->texture_ = window->loadTexture(("res/assets/units/" + country + name + ".gif").c_str());

  return unit;
}

std::string Unit::getName() {
  return name_;
}

std::string Unit::getCountry() {
  return name_;
}

SDL_Texture* Unit::getTexture() {
  return texture_;
}

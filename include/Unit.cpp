#include "Unit.hpp"
#include "GIFWrapper.hpp"
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

  unit->setGIF("res/assets/units/" + country + name + ".gif");
  unit->getGIF()->setFrameNumber(0);

  return unit;
}

std::string Unit::getName() { return name_; }
std::string Unit::getCountry() { return name_; }
GIFImage* Unit::getGIF() { return &gif_; }

void Unit::setName(std::string name) { name_ = name; }
void Unit::setCountry(std::string country) { country_ = country; }
void Unit::setGIF(std::string path) { gif_ = GIFImage(path, window_); }

#include "Unit.hpp"
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <string>

Unit::Unit(std::string country, std::string name, RenderWindow* window) :
  country_{country}, name_{name}, window_{window},
  gif_{GIFImage("res/assets/units/" + country + name + ".gif", scaling_, window)} {};

Unit* Unit::createUnit(std::string country, std::string name, RenderWindow* window) {
  Unit* unit = new Unit(country, name, window);
  return unit;
}

std::string Unit::getName() { return name_; }
std::string Unit::getCountry() { return name_; }
GIFImage* Unit::getGIF() { return &gif_; }

void Unit::setName(std::string name) { name_ = name; }
void Unit::setCountry(std::string country) { country_ = country; }
void Unit::setGIF(std::string path) { gif_ = GIFImage(path, scaling_, window_); }

void Unit::setScaling(int scaling) { scaling_ = scaling; };

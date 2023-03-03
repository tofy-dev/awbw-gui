#include "Unit.hpp"
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <string>

// constructors + static functions
Unit::Unit(std::string country, std::string name, RenderWindow* window) :
  country_{country}, name_{name}, window_{window},
  gif_{GIFImage::createGIF("res/assets/units/" + country + name + ".gif", scaling_, window)} {};

Unit* Unit::createUnit(std::string country, std::string name, RenderWindow* window) {
  if (country == "random")
    country = nat_arr_[rand()%NATION_AMT];
  Unit* unit = new Unit(country, name, window);
  return unit;
}

void Unit::destroyUnit(Unit* unit) {
  GIFImage::destroyGIF(unit->gif_);
  delete unit;
}

void Unit::setScaling(double scaling) { scaling_ = scaling; };


// getters
std::string Unit::getName() { return name_; }

std::string Unit::getCountry() { return name_; }

GIFImage* Unit::getGIF() { return gif_; }


// setters
void Unit::setName(std::string name) { name_ = name; }

void Unit::setCountry(std::string country) { country_ = country; }

void Unit::setGIF(std::string path) { gif_ = GIFImage::createGIF(path, scaling_, window_); }

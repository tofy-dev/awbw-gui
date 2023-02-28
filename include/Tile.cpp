#pragma once
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include "GIFWrapper.hpp"
#include "Tile.hpp"
#include "RenderWindow.hpp"

#define DNE std::string::npos

// tile ============================================================================================
Tile::Tile(int id, RenderWindow* window) : 
  id_{id}, window_(window),
  gif_{GIFImage("res/assets/tiles/" + getName(id) + ".gif", scaling_, window)} {};

Tile* Tile::createTile(int id, RenderWindow* window) {
  std::string name = Tile::getName(id);
  std::string path = "res/assets/tiles/" + name + ".gif";

  Tile* tile;
  if (name.find("city") != DNE)
    tile = (new City(id, window));
  else if (name.find("base") != DNE)
    tile = (new Base(id, window));
  else if (name.find("airport") != DNE)
    tile = (new Airport(id, window));
  else if (name.find("port") != DNE)
    tile = (new Port(id, window));
  else if (name.find("hq") != DNE)
    tile = (new HQ(id, window));
  else if (name.find("lab") != DNE)
    tile = (new Lab(id, window));
  else if (name.find("comtower") != DNE)
    tile = (new ComTower(id, window));
  else if (name.find("mountain") != DNE)
    tile = (new Mountain(id, window));
  else
    tile = (new Terrain(id, window));
  return tile;
}

Unit* Tile::getUnit() { return unit_; }
std::array<int, 2> Tile::getDims(int basic) {
  return {basic, basic*h_mult_/16};
}
void Tile::setUnit(Unit* unit) {
  if (unit_ != nullptr) SDL_free(unit_);
  unit_ = unit;
}

int Tile::getId() { return id_; }

GIFImage* Tile::getGIF() { return &gif_; }


// static functions
std::string Tile::getName(int id) {
  std::string name = terrain_list_[id];
  name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char x) { return std::isspace(x); }), name.end());
  for (int i = 0; i < name.size(); i++)
    name[i] = tolower(name[i]);
  return name;
}
void Tile::setScaling(int scaling) { scaling_ = scaling; };
// tile ============================================================================================

City::~City() {};
void City::onClick() {
  std::cout << "city" << '\n';
}

Base::~Base() {};
void Base::onClick() {
  std::cout << "base" << '\n';
}

Airport::~Airport() {};
void Airport::onClick() {
  std::cout << "airport" << '\n';
}

Port::~Port() {};
void Port::onClick() {
  std::cout << "port" << '\n';
}

HQ::~HQ() {};
void HQ::onClick() {
  std::cout << "hq" << '\n';
}

Lab::~Lab() {};
void Lab::onClick() {
  std::cout << "lab" << '\n';
}

ComTower::~ComTower() {};
void ComTower::onClick() {
  std::cout << "comtower" << '\n';
}

Mountain::~Mountain() {};
void Mountain::onClick() {
  std::cout << "mountain" << '\n';
}

Terrain::~Terrain() {};
void Terrain::onClick() {
  std::cout << "terrain/" << getName(id_) << '\n';
}

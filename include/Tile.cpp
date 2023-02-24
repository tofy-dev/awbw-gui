#pragma once
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Tile.hpp"
#include "RenderWindow.hpp"

#define DNE std::string::npos

// tile ============================================================================================
Tile::Tile(int id, RenderWindow* window) : id_{id}, window_(window) {
  texture_ = window->loadTexture(("res/assets/tiles/" + getName(id) + ".gif").c_str());
}

std::unique_ptr<Tile> Tile::createTile(int id, RenderWindow* window) {
  std::string name = Tile::getName(id);
  std::unique_ptr<Tile> ptr;
  if (name.find("city") != DNE)
    ptr = std::make_unique<City>(id, window);
  else if (name.find("base") != DNE)
    ptr = std::make_unique<Base>(id, window);
  else if (name.find("airport") != DNE)
    ptr = std::make_unique<Airport>(id, window);
  else if (name.find("port") != DNE)
    ptr = std::make_unique<Port>(id, window);
  else if (name.find("hq") != DNE)
    ptr = std::make_unique<HQ>(id, window);
  else if (name.find("lab") != DNE)
    ptr = std::make_unique<Lab>(id, window);
  else if (name.find("comtower") != DNE)
    ptr = std::make_unique<ComTower>(id, window);
  else if (name.find("mountain") != DNE)
    ptr = std::make_unique<Mountain>(id, window);
  else
    ptr = std::make_unique<Terrain>(id, window);
  return ptr;
}

std::array<int, 2> Tile::getDims(int basic) {
  return {basic, basic*h_mult_/16};
}
std::string Tile::getName(int id) {
  std::string name = terrain_list_[id];
  name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char x) { return std::isspace(x); }), name.end());
  for (int i = 0; i < name.size(); i++) {
    name[i] = tolower(name[i]);
  }
  return name;
}
int Tile::getId() {
  return id_;
}
void Tile::setUnit(Unit* unit) {
  unit_ = unit;
}
Unit* Tile::getUnit() {
  return unit_;
}
SDL_Texture* Tile::getTexture() {
  return texture_;
}
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

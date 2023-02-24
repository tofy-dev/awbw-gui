#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include "Tile.hpp"
#include "RenderWindow.hpp"

#define DNE std::string::npos

Tile::Tile(int id, RenderWindow* window) : id_{id}, window_(window) {
  texture_ = window->loadTexture(("res/assets/tiles/" + getName() + ".gif").c_str());
}

void Tile::onClick() {
  std::cout << getName() + " clicked!" << '\n';
}

int Tile::getId() {
  return id_;
}

bool Tile::isActive() {
  return active_;
}

std::string Tile::getName() {
  std::string name = terrain_list_[id_];
  name.erase(std::remove_if(name.begin(), name.end(), [](unsigned char x) { return std::isspace(x); }), name.end());
  for (int i = 0; i < name.size(); i++) {
    name[i] = tolower(name[i]);
  }
  return name;
}

std::array<int, 2> Tile::getDims(int basic) {
  std::string name = getName();
  if (name.find("airport") != DNE) return {basic, basic*18/16};
  if (name.find("base") != DNE) return {basic, basic*25/16};
  if (name.find("port") != DNE) return {basic, basic*22/16};
  if (name.find("city") != DNE) return {basic, basic*22/16};
  if (name.find("comtower") != DNE) return {basic, basic*25/16};
  if (name.find("hq") != DNE) return {basic, basic*31/16};
  if (name.find("lab") != DNE) return {basic, basic*24/16};
  if (name.find("mountain") != DNE) return {basic, basic*21/16};
  return {basic, basic};
}

SDL_Texture* Tile::getTexture() {
  return texture_;
}

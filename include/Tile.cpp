#include "Tile.hpp"

Tile::Tile(int id) : id_{id} {
  // load texture
}

int Tile::getId() {
  return id_;
}

bool Tile::isActive() {
  return active_;
}

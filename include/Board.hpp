#pragma once
#include <SDL2/SDL_events.h>
#include <vector>
#include <string>
#include <memory>
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include "Unit.hpp"

class Board {
public:
  Board(std::string path, RenderWindow* window);
  void handleClick(SDL_MouseButtonEvent*);
  void renderBoard();
  void addUnit(std::string country, std::string name, int x, int y);
  void wipeUnits();

private:
  // note: coordinates in AWBW are x by y, top-left origin, 0 indexed
  RenderWindow* window_;
  std::vector<std::vector<std::unique_ptr<Tile>>> grid_;
  int rows_ = 0, cols_ = 0;
};

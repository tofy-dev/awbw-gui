#pragma once
#include <SDL2/SDL_events.h>
#include <vector>
#include <string>
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include "Unit.hpp"

class Board {
public:
  Board(std::string path, RenderWindow* window);
  ~Board();

  void handleClick(SDL_MouseButtonEvent*);
  void renderBoard();
  void wipeUnits();
  void flash();

private:
  Unit* unit_storage_ = nullptr;

  RenderWindow* window_;
  std::vector<std::vector<Tile*>> grid_;
  int rows_ = 0, cols_ = 0;
};

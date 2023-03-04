#pragma once
#include <SDL2/SDL_events.h>
#include <vector>
#include <string>
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include "Unit.hpp"

#define SCALE 30

class Board {
public:
  Board(std::string path, RenderWindow* window);
  ~Board();

  void handleClick(SDL_MouseButtonEvent* event);
  void renderBoard();
  void updateFrames(int amount);
  void wipeUnits();

  int getWidth();
  int getHeight();

private:
  Unit* unit_storage_ = nullptr;

  RenderWindow* window_;
  std::vector<std::vector<Tile*>> grid_;
  int rows_ = 0, cols_ = 0;
};

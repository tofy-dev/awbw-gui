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
  std::vector<std::vector<Tile*>> grid_;
  std::vector<Unit*> units_;
  Unit* unit_storage_ = nullptr;

  int rows_ = 0, cols_ = 0;
  RenderWindow* window_;

  // TODO: delete
  GIFImage* blue;
};

#pragma once
#include "RenderWindow.hpp"
#include "Tile.hpp"
#include <vector>
#include <string>

class Board {
public:
  Board(std::string path, RenderWindow* window);
  void handleClick();
  void renderBoard();
  void printBoardIds();

private:
  // note: coordinates in AWBW are x by y, top-left origin, 0 indexed
  RenderWindow* window_;
  std::vector<std::vector<Tile>> grid_;
  int rows_ = 0, cols_ = 0;
};

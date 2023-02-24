#include "Board.hpp"
#include "Tile.hpp"
#include "RenderWindow.hpp"
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>

#define SIZE 30

Board::Board(std::string path, RenderWindow* window) : window_(window) {
  freopen(path.c_str(), "r", stdin);
  std::string line;

  while (std::getline(std::cin, line)) {
    std::vector<Tile> row;
    int s = 0;
    for (int i = 0; i <= line.size(); i++) {
      if (i == line.size() || line.at(i) == ',') {
        row.push_back(Tile(std::stoi(line.substr(s,i-s)), window));
        s = i+1;
        if (rows_ == 0) cols_++;
      }
    }
    grid_.push_back(row);
    rows_++;
  }

  std::cout << rows_ << " by " << cols_ << '\n';
  printBoardIds();
}

void Board::handleClick() {

}

void Board::renderBoard() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      int width = grid_[r][c].getDims(SIZE)[0];
      int height = grid_[r][c].getDims(SIZE)[1];

      SDL_Rect src; src.x = 0; src.y = 0; src.w = width; src.h = height;
      SDL_Rect dst; dst.x = SIZE*c; dst.y = SIZE*r-(height-SIZE); dst.w = width; dst.h = height;

      window_->render(grid_[r][c].getTexture(), src, dst);
    }
  }
}

void Board::printBoardIds() {
  for (int r = 0; r < grid_.size(); r++) {
    for (int c = 0; c < grid_[r].size(); c++) {
      std::cout << grid_[r][c].getId() << ((c == grid_[r].size()-1) ? "\n" : " ");
    }
  }
}

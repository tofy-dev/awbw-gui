#include <SDL2/SDL_events.h>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "Board.hpp"
#include "Tile.hpp"
#include "RenderWindow.hpp"

#define SIZE 30

Board::Board(std::string path, RenderWindow* window) : window_(window) {
  freopen(path.c_str(), "r", stdin);
  std::string line;

  while (std::getline(std::cin, line)) {
    std::vector<std::unique_ptr<Tile>> row;
    int s = 0;
    for (int i = 0; i <= line.size(); i++) {
      if (i == line.size() || line.at(i) == ',') {
        int id = std::stoi(line.substr(s,i-s));
        row.push_back(Tile::createTile(id, window));
        s = i+1;
        if (rows_ == 0) cols_++;
      }
    }
    grid_.push_back(std::move(row));
    rows_++;
  }

  std::cout << rows_ << " by " << cols_ << '\n';
  printBoardIds();
  
  // TODO : DELETE!!!!!!!!!!!!!!!!!!!
  foo_ = Tile::createTile(1, window);
  Unit un("bh", "mech", 0, 0, window);
  foo_->setUnit(&un);
}

void Board::addUnit(std::string country, std::string name, int x, int y) {
  Unit un(country, name, x, y, window_);
  grid_[y][x]->setUnit(&un);
}

void Board::handleClick(SDL_MouseButtonEvent* event) {
  int x = event->x, y = event->y;
  if (y >= rows_*SIZE || x >= cols_*SIZE) return;

  grid_[y/SIZE][x/SIZE]->onClick();
  addUnit("bh", "mech", x/SIZE, y/SIZE);
  window_->display();
}

void Board::renderBoard() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      int width = grid_[r][c]->getDims(SIZE)[0];
      int height = grid_[r][c]->getDims(SIZE)[1];

      SDL_Rect src; src.x = 0; src.y = 0; src.w = width; src.h = height;
      SDL_Rect dst; dst.x = SIZE*c; dst.y = SIZE*r-(height-SIZE); dst.w = width; dst.h = height;

      window_->render(grid_[r][c]->getTexture(), src, dst);
      if (grid_[r][c]->getUnit() != NULL) {
        std::cout << r << " " << c << '\n';
        src.x = 0; src.y = 0; src.w = SIZE; src.h = SIZE;
        dst.x = SIZE*c; dst.y = SIZE*r; dst.w = SIZE; dst.h = SIZE;

        // window_->render(grid_[r][c]->getUnit()->getTexture(), src, dst);
        // window_->render(un.getTexture(), src, dst);
        // window_->render(window_->loadTexture(("res/assets/units/bhmech.gif")), src, dst);
      }
    }
  }

  window_->render(foo_->getUnit()->getTexture(), SDL_Rect(),SDL_Rect());
}

void Board::printBoardIds() {
  for (int r = 0; r < grid_.size(); r++) {
    for (int c = 0; c < grid_[r].size(); c++) {
      std::cout << grid_[r][c]->getId() << ((c == grid_[r].size()-1) ? "\n" : " ");
    }
  }
}

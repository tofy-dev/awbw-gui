#include <SDL2/SDL_events.h>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "Board.hpp"
#include "GIFWrapper.hpp"
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
}

void Board::handleClick(SDL_MouseButtonEvent* event) {
  int x = event->x, y = event->y;
  if (y >= rows_*SIZE || x >= cols_*SIZE) return;
  switch (event->button) {
    case SDL_BUTTON_LEFT:
      addUnit("os", "mech", x/SIZE, y/SIZE);
      break;
    case SDL_BUTTON_RIGHT:
      addUnit("bh", "mech", x/SIZE, y/SIZE);
      break;
  }
  grid_[y/SIZE][x/SIZE]->onClick();
}

void Board::renderBoard() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      int width = grid_[r][c]->getDims(SIZE)[0];
      int height = grid_[r][c]->getDims(SIZE)[1];

      SDL_Rect src; src.x = 0; src.y = 0; src.w = width; src.h = height;
      SDL_Rect dst; dst.x = SIZE*c; dst.y = SIZE*r-(height-SIZE); dst.w = width; dst.h = height;

      window_->render(grid_[r][c]->getTexture(), src, dst);
      if (grid_[r][c]->getUnit() != nullptr) {
        src.x = 0; src.y = 0; src.w = SIZE; src.h = SIZE;
        dst.x = SIZE*c; dst.y = SIZE*r; dst.w = SIZE; dst.h = SIZE;

        window_->render(grid_[r][c]->getUnit()->getTexture(), src, dst);
      }
    }
  }
}

// TODO: bad naming, temp
void Board::flash() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      GIFImage* gif = grid_[r][c]->getGIF();
      gif->setFrameNumber((gif->getFrameNumber() + 1) % gif->getTotalFrames());
      if (grid_[r][c]->getUnit() != nullptr) {
        GIFImage* gif2 = grid_[r][c]->getUnit()->getGIF();
        gif2->setFrameNumber((gif2->getFrameNumber() + 1) % gif2->getTotalFrames());
        std::cout << gif2->getFrameNumber() << '\n';
      }
    }
  }
}

void Board::addUnit(std::string country, std::string name, int x, int y) {
  grid_[y][x]->setUnit(Unit::createUnit(country, name, window_));
}

void Board::wipeUnits() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      grid_[r][c]->setUnit(nullptr);
    }
  }
}

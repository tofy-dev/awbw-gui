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

#define SCALE 30

Board::Board(std::string path, RenderWindow* window) : window_(window) {
  Tile::setScaling(SCALE/16.f);
  Unit::setScaling(SCALE/16.f);

  freopen(path.c_str(), "r", stdin);
  std::string line;

  while (std::getline(std::cin, line)) {
    std::vector<Tile*> row;
    int s = 0;
    for (int i = 0; i <= line.size(); i++) {
      if (i == line.size() || line.at(i) == ',') {
        int id = std::stoi(line.substr(s,i-s));
        row.push_back(Tile::createTile(id, window));
        s = i+1;
        if (rows_ == 0) cols_++;
      }
    }
    grid_.push_back(row);
    rows_++;
  }

  std::cout << rows_ << " by " << cols_ << '\n';
}

void Board::handleClick(SDL_MouseButtonEvent* event) {
  int x = event->x, y = event->y;
  if (y >= rows_*SCALE || x >= cols_*SCALE) return;
  switch (event->button) {
    case SDL_BUTTON_LEFT:
      addUnit("os", "b-copter", x/SCALE, y/SCALE);
      break;
    case SDL_BUTTON_RIGHT:
      addUnit("bh", "b-copter", x/SCALE, y/SCALE);
      break;
  }
  grid_[y/SCALE][x/SCALE]->onClick();
}

void Board::renderBoard() {
  SDL_Rect dst;
  Tile* tile;
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      tile = grid_[r][c];
      int w = tile->getGIF()->getWidth();
      int h = tile->getGIF()->getHeight();

      dst.x = w*c; dst.y = w*r-(h-w);
      dst.w = w; dst.h = h;

      window_->render(tile->getGIF()->getTexture(), dst);

      if (tile->getUnit() != nullptr) {
        dst.x = w*c; dst.y = w*r;
        dst.w = SCALE; dst.h = SCALE;

        window_->render(tile->getUnit()->getGIF()->getTexture(), dst);
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

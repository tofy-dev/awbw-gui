#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <cassert>


#include "Board.hpp"
#include "GIFWrapper.hpp"
#include "Tile.hpp"
#include "RenderWindow.hpp"

// constructors + static functions
Board::Board(std::string path, RenderWindow* window) : window_(window) {
  Tile::setScaling(SCALE/16.f);
  Unit::setScaling(SCALE/16.f);

  FILE* fp = freopen(path.c_str(), "r", stdin);
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

  fclose(fp);
  std::cout << "before blue\n";
  blue = GIFImage::createGIF("res/assets/custom/blue.gif", SCALE/16.f, window_);
  std::cout << "finish initing board\n";
}

Board::~Board() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      std::cout << r << " " << c << '\n';
      if (grid_[r][c]->getUnit() != nullptr)
        Unit::destroyUnit(grid_[r][c]->getUnit());
      Tile::destroyTile(grid_[r][c]);
    }
  }     
}

void Board::handleClick(SDL_MouseButtonEvent* event) {
  int x = event->x, y = event->y;
  if (y >= rows_*SCALE || x >= cols_*SCALE) return;
  Tile* tile = grid_[y/SCALE][x/SCALE];

  if (unit_storage_ != nullptr) {
    if (tile->getUnit() != nullptr) return;
    tile->setUnit(unit_storage_);
    unit_storage_ = nullptr;
  } else if (tile->getUnit() != nullptr) {
    unit_storage_ = tile->getUnit();
    tile->setUnit(nullptr, false);
  } else {
    Unit* unit;
    switch (event->button) {
      case SDL_BUTTON_LEFT:
        unit = Unit::createUnit("os", "mech", window_);
        break;
      case SDL_BUTTON_RIGHT:
        unit = Unit::createUnit("bm", "mech", window_);
        break;
    }
    tile->setUnit(unit);
    units_.push_back(unit);
  }
  tile->onClick();
}

void Board::updateFrames(int amount) {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      GIFImage* gif = grid_[r][c]->getGIF();
      gif->getFrame()->ticks_ += amount;
      if (gif->getFrame()->ticks_ >= gif->getFrame()->delay_) {
        gif->setFrameNumber((gif->getFrameNumber() + 1) % gif->getTotalFrames());
        gif->getFrame()->ticks_ = 0;
      }

      if (grid_[r][c]->getUnit() != nullptr) {
        GIFImage* gif2 = grid_[r][c]->getUnit()->getGIF();
        gif2->getFrame()->ticks_ += amount;
        if (gif2->getFrame()->ticks_ == gif2->getFrame()->delay_) {
          gif2->setFrameNumber((gif2->getFrameNumber() + 1) % gif2->getTotalFrames());
          gif2->getFrame()->ticks_ = 0;
        }
      }
    }
  }
}

void Board::renderBoard() {
  SDL_Rect dst;
  Tile* tile;
  Unit* unit;

  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      tile = grid_[r][c];
      int w = tile->getGIF()->getWidth();
      int h = tile->getGIF()->getHeight();

      dst.x = w*c; dst.y = w*r-(h-w);
      dst.w = w; dst.h = h;

      window_->render(tile->getGIF()->getTexture(), dst);

      unit = tile->getUnit();
      if (unit != nullptr) {
        dst.x = w*c; dst.y = w*r;
        dst.w = unit->getGIF()->getWidth(); dst.h = unit->getGIF()->getHeight();

        window_->render(tile->getUnit()->getGIF()->getTexture(), dst);
        window_->render(blue->getTexture(), dst);
      }
    }
  }
}

void Board::wipeUnits() {
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      grid_[r][c]->setUnit(nullptr);
    }
  }
}


int Board::getWidth() { return cols_; }

int Board::getHeight() { return rows_; }

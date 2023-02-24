#pragma once
#include <string>

class Board {
public:
  Board(std::string path);
private:
  int rows_, cols_;
};

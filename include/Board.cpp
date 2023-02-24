#include "Board.hpp"
#include <cstdio>
#include <string>
#include <iostream>

Board::Board(std::string path) {
  freopen(path.c_str(), "r", stdin);
  std::string line;
  while (std::getline(std::cin, line)) {
    int s = 0;
    for (int i = 0; i <= line.size(); i++) {
      if (i == line.size() || line.at(i) == ',') {
        std::cout << line.substr(s,i-s) << ' ';
        s = i+1;
      }
    }
    std::cout << '\n';
  }
}

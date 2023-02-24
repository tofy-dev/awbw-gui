#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_events.h"
#include <iostream>

#include "RenderWindow.hpp"
#include "Board.hpp"
#include "Unit.hpp"
#include "Tile.hpp"

int main(int argc, char* args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    std::cout << "SDL_Init fails with error: " << SDL_GetError() << '\n';
  }

  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cout << "IMG_Init fails with error: " << SDL_GetError() << '\n';
  }

  RenderWindow window("Test", 1280, 720);

  bool running = true;
  SDL_Event event;
  Board board("res/inputs/shadowsendlessly.txt", &window);

  board.renderBoard();
  window.display();

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        board.handleClick(&event.button);
        board.renderBoard();
      }
    }
  }

  SDL_Quit();

  return 0;
}

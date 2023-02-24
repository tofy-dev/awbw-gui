#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_events.h"
#include <iostream>

#include "RenderWindow.hpp"
#include "Board.hpp"

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
  Board b("res/inputs/stalingrad.txt");

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }

    window.clear();
    SDL_Rect src;
    src.x = 0; src.y = 0; src.w = 490; src.h = 490;

    SDL_Rect dst;
    dst.x = 0; dst.y = 0; dst.w = 490; dst.h = 490;
    window.render(window.loadTexture("res/assets/bcopter.png"), src, dst);
    window.display();
  }

  SDL_Quit();

  return 0;
}

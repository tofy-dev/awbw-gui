#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_events.h"
#include <iostream>

#include "RenderWindow.hpp"
#include "Board.hpp"
#include "Unit.hpp"
#include "Tile.hpp"
#include "FPSTimer.hpp"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char* args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    std::cout << "SDL_Init fails with error: " << SDL_GetError() << '\n';
  }

  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cout << "IMG_Init fails with error: " << SDL_GetError() << '\n';
  }

  RenderWindow window("awbw gui", 1280, 720);
  window.display();

  Board board("res/inputs/stalingrad.txt", &window);
  board.renderBoard();
  window.display();

  bool running = true;
  int frame = 0;
  SDL_Event event;

  LTimer fpsTimer;
  LTimer capTimer;

  int countedFrames = 0;
  fpsTimer.start();

  while (running) {
    capTimer.start(); 
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        board.handleClick(&event.button);
        board.renderBoard();
        window.display();
      }
    }

    ++countedFrames;
    int frameTicks = capTimer.getTicks();
    if( frameTicks < SCREEN_TICKS_PER_FRAME ) {
        SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
    }
  }

  SDL_Quit();

  return 0;
}
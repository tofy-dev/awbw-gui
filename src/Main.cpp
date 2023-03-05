#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_events.h"
#include <SDL2/SDL_render.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Board.hpp"
#include "Unit.hpp"
#include "Tile.hpp"
#include "FPSTimer.hpp"
#include "GIFWrapper.hpp"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main(int argc, char* args[]) {
  if (SDL_Init(SDL_INIT_VIDEO) > 0) {
    std::cout << "SDL_Init fails with error: " << SDL_GetError() << '\n';
  }

  if (!(IMG_Init(IMG_INIT_PNG))) {
    std::cout << "IMG_Init fails with error: " << SDL_GetError() << '\n';
  }

  std::string input_path = "res/inputs/stalingrad.txt";
  RenderWindow window("AWBW Gui", 0, 0);
  Board board(input_path, &window);
  window.setSize(SCALE*board.getWidth(), SCALE*board.getHeight());

  board.renderBoard();
  window.display();

  bool running = true;
  int frame = 0;
  SDL_Event event;

  LTimer cap_timer;

  while (running) {
    cap_timer.start(); 
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        board.handleClick(&event.button);
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
          board.wipeUnits();
        }
      }
    }

    board.updateFrames(SCREEN_TICKS_PER_FRAME);
    board.renderBoard();
    window.display();

    int cap_ticks = cap_timer.getTicks();
    if (cap_ticks < SCREEN_TICKS_PER_FRAME ) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - cap_ticks);
    }
    cap_timer.stop();
  }

  SDL_Quit();

  return 0;
}

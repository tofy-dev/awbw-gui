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

  RenderWindow window("awbw gui", 1280, 720);
  Tile::setScaling(5);
  Unit::setScaling(5);

  Tile* plain = Tile::createTile(1, &window);
  Tile* hq = Tile::createTile(95, &window);

  SDL_Texture* pntex = plain->getGIF()->getTexture();
  SDL_Texture* hqtex = hq->getGIF()->getTexture();

  SDL_Rect a, b;
  a.h = plain->getGIF()->getHeight(); a.w = plain->getGIF()->getWidth();
  a.x = 0; a.y = 0;

  b.h = plain->getGIF()->getHeight(); b.w = plain->getGIF()->getWidth();
  b.x = 0; b.y = b.h-(b.h-a.h);
  
  window.render(pntex, plain->getGIF()->getDims());
  window.render(hqtex, hq->getGIF()->getDims());

  window.display();

  bool running = true;
  SDL_Event event;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = false;
    }
  }
  /*
  Board board("res/inputs/stalingrad.txt", &window);
  board.renderBoard();
  window.display();

  bool running = true;
  int frame = 0;
  SDL_Event event;

  LTimer capTimer;
  LTimer animTimer;
  animTimer.start();
  while (running) {
    capTimer.start(); 
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
    // TODO: make not arbitrary
    int animTicks = animTimer.getTicks();
    if (animTicks >= SCREEN_TICKS_PER_FRAME*50) {
      board.flash();
      animTimer.stop();
      animTimer.start();
    }
    board.renderBoard();
    window.display();

    int capTicks = capTimer.getTicks();
    if (capTicks < SCREEN_TICKS_PER_FRAME ) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - capTicks);
    }
    capTimer.stop();
  }
  */

  SDL_DestroyTexture(pntex);
  SDL_DestroyTexture(hqtex);
  SDL_Quit();

  return 0;
}

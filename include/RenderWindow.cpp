#include "RenderWindow.hpp"
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>

// constructors
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) : window_(NULL), renderer_(NULL) {
  window_ = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window_ == NULL) {
    std::cout << "SDL_CreateWindow failed with error: " << SDL_GetError() << '\n';
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

RenderWindow::~RenderWindow() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  std::cout << "Window destroyed.\n";
}


// functions
SDL_Texture* RenderWindow::loadTexture(const char* p_filePath) {
  SDL_Texture* texture = NULL;
  texture = IMG_LoadTexture(renderer_, p_filePath);

  if (texture == NULL)
    std::cout << "Failed to load texture with error: " << SDL_GetError() << '\n';

  return texture;
}

SDL_Texture* RenderWindow::loadTexture(SDL_Surface* p_surface) {
  return SDL_CreateTextureFromSurface(renderer_, p_surface);
}

void RenderWindow::clear() {
  SDL_RenderClear(renderer_);
}

void RenderWindow::render(SDL_Texture* p_tex) {
  SDL_RenderCopy(renderer_, p_tex, NULL, NULL);
}

void RenderWindow::render(SDL_Texture* p_tex, SDL_Rect p_dst) {
  SDL_RenderCopy(renderer_, p_tex, NULL, &p_dst);
}

void RenderWindow::display() {
  SDL_RenderPresent(renderer_);
}

void RenderWindow::setSize(int w, int h) {
  SDL_SetWindowSize(window_, w, h);
}

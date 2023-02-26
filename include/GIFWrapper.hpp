#pragma once
#include <gif_lib.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <string>
#include <vector>

class GIFFrame {
public:
  int width_, height_;
  SDL_Palette* palette_;
  SDL_Surface* surface_;

private:
};

class GIFImage {
#include "GIFWrapper.hpp"
public:
  GIFImage();
  GIFImage(std::string path);
  void setFrameNumber(int frame_num);
  int getFrameNumber();
  int getTotalFrames();
  GIFFrame* getFrame();

  static SDL_Surface* createSurface(int width, int height);
  static void setPixel(SDL_Surface* surface, int x, int y, Uint32 color);

private:
  int width_, height_;
  int total_frames_;

  std::vector<GIFFrame*> frames_;
  int frame_num_;
};

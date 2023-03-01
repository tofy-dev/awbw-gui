#pragma once
#include "RenderWindow.hpp"
#include <gif_lib.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <vector>

class GIFFrame {
public:
  int raw_w_, raw_h_;

  int disposal_method_;
  SDL_Texture* texture_;
  SDL_Surface* surface_;

private:
};

class GIFImage {
#include "GIFWrapper.hpp"
public:
  ~GIFImage();
  GIFImage(std::string path, double scale, RenderWindow* window);

  bool shouldOverlay(int frame_num);

  void setFrameNumber(int frame_num);
  int getFrameNumber();
  SDL_Texture* getTexture();
  SDL_Rect getDims();
  int getTotalFrames();
  GIFFrame* getFrame();

  int getWidth();
  int getHeight();

  static SDL_Surface* createSurface(int width, int height);
  static void setPixel(SDL_Surface* surface, int x, int y, Uint32 color);

private:
  int max_w_, max_h_;
  int total_frames_;

  std::vector<GIFFrame*> frames_;
  int frame_num_;
};

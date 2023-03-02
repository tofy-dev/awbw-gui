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
  GIFImage(std::string path, double scale, RenderWindow* window);
  static GIFImage* createGIF(std::string path, double scale, RenderWindow* window);
  static void destroyGIF(GIFImage* image);
  static SDL_Surface* createSurface(int width, int height);
  static void setPixel(SDL_Surface* surface, int x, int y, Uint32 color);

  bool shouldOverlay(int frame_num);
  SDL_Texture* getTexture();
  GIFFrame* getFrame();
  int getTotalFrames();
  int getFrameNumber();

  int getWidth();
  int getHeight();
  SDL_Rect getDims();

  void setFrameNumber(int frame_num);


private:
  int max_w_, max_h_;
  int total_frames_;

  std::vector<GIFFrame*> frames_;
  int frame_num_;
};

#pragma once
#include <gif_lib.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_pixels.h>
#include <string>
#include <vector>

class GIFFrame {
public:
  void setPalette(SDL_Palette* palette) { palette_ = palette; };
  void setSurface(SDL_Surface* surface) { surface_ = surface; };
  SDL_Palette* getPalette() { return palette_; };
  SDL_Surface* getSurface() { return surface_; };

  // Public for easier accesibility
  int left_off_, top_off_;
  int width_, height_;

  SDL_Color transparent_color_;
  bool transparent_;
  int trans_idx_;

  bool has_surface_ = SDL_FALSE;

private:
  SDL_Palette* palette_;
  SDL_Surface* surface_;
};

class GIFImage {
#include "GIFWrapper.hpp"
public:
  GIFImage(std::string path);
  void setFrameNumber(int frame_num);
  int getFrameNumber();
  GIFFrame* getFrame();

  static void createPalette(SDL_Palette* palette, ColorMapObject* map);
  static SDL_Surface* createSurface(int width, int height);
  static void setPixel(SDL_Surface* surface, int x, int y, Uint32 color);

private:
  int width_, height_;
  int total_frames_;

  std::vector<GIFFrame*> frames_;
  int frame_num_;

  SDL_Palette* global_palette_;
  GifFileType* file_;
  int error_ = -69;
};

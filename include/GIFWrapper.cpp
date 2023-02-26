/*
 * Copied from https://github.com/grimfang4/SDL_gifwrap
 */

#pragma once
#include "GIFWrapper.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <vector>
#include <gif_lib.h>
#include <iostream>
#include <string>
#include <cassert>

GIFImage::GIFImage(std::string path) {
  GifFileType* gif;
  int error = -1;
  gif = DGifOpenFileName(path.c_str(), &error);
  assert(gif != NULL && DGifSlurp(gif) != GIF_ERROR);

  SDL_Color* global_colors = (SDL_Color*)SDL_malloc(sizeof(SDL_Color)*gif->SColorMap->ColorCount);
  for (int i = 0; i < gif->SColorMap->ColorCount; i++) {
    global_colors[i].r = gif->SColorMap->Colors[i].Red;
    global_colors[i].g = gif->SColorMap->Colors[i].Green;
    global_colors[i].b = gif->SColorMap->Colors[i].Blue;
    global_colors[i].a = 255;
  }

  frames_ = std::vector<GIFFrame*>(gif->ImageCount);
  for (int f = 0; f < gif->ImageCount; f++) {
    SavedImage* img = &gif->SavedImages[f];
    GIFFrame* frame = (GIFFrame*)SDL_malloc(sizeof(GIFFrame));
    memset(frame, 0, sizeof(GIFFrame));

    SDL_Color* local_colors = NULL;
    if (img->ImageDesc.ColorMap == NULL) {
      local_colors = (SDL_Color*)SDL_malloc(sizeof(SDL_Color)*gif->SColorMap->ColorCount);
    }

    frames_[f] = frame;
    frame->width_ = img->ImageDesc.Width;
    frame->height_ = img->ImageDesc.Height;

    // TODO: transparency
    int total_pixels = frame->width_ * frame->height_;
    frame->surface_ = createSurface(frame->width_, frame->height_);
    
    SDL_Color* color_src = (local_colors == NULL) ? global_colors : local_colors;
    for (int p = 0; p < total_pixels; p++) {
      SDL_Color c = color_src[img->RasterBits[p]];
      setPixel(frame->surface_, p%frame->width_, p/frame->width_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
    }

    free(local_colors);
  }
  free(global_colors);
  DGifCloseFile(gif, &error);
}

SDL_Surface* GIFImage::createSurface(int width, int height) {
  return SDL_CreateRGBSurface(0,width,height,32,0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
}

void GIFImage::setPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* bits = ((Uint8 *)surface->pixels) + y*surface->pitch + x*bpp;

    /* Set the pixel */
    switch(bpp)
    {
        case 1:
            *((Uint8 *)(bits)) = (Uint8)color;
            break;
        case 2:
            *((Uint16 *)(bits)) = (Uint16)color;
            break;
        case 3: { /* Format/endian independent */
            Uint8 r,g,b;
            r = (color >> surface->format->Rshift) & 0xFF;
            g = (color >> surface->format->Gshift) & 0xFF;
            b = (color >> surface->format->Bshift) & 0xFF;
            *((bits)+surface->format->Rshift/8) = r;
            *((bits)+surface->format->Gshift/8) = g;
            *((bits)+surface->format->Bshift/8) = b;
            }
            break;
        case 4:
            *((Uint32 *)(bits)) = (Uint32)color;
            break;
    }
}

void GIFImage::setFrameNumber(int frame_num) {
  frame_num_ = frame_num;
}

int GIFImage::getFrameNumber() {
  return frame_num_;
}

GIFFrame* GIFImage::getFrame() {
  return frames_[frame_num_];
}

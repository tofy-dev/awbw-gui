/*
 * Poopy implementation of https://github.com/grimfang4/SDL_gifwrap
 */

#pragma once
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <vector>
#include <gif_lib.h>
#include <iostream>
#include <string>
#include <cassert>

GIFImage::~GIFImage() {
  for (int f = 0; f < total_frames_; f++) {
    GIFFrame* frame = frames_[f];
    SDL_FreeSurface(frame->surface_);
    SDL_DestroyTexture(frame->texture_);
  }
}

GIFImage::GIFImage(std::string path, RenderWindow* window) {
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
  assert(global_colors != NULL);

  total_frames_ = gif->ImageCount;
  frame_num_ = 0;

  frames_ = std::vector<GIFFrame*>(gif->ImageCount);
  for (int f = 0; f < gif->ImageCount; f++) {
    SavedImage* img = &gif->SavedImages[f];
    GIFFrame* frame = (GIFFrame*)SDL_malloc(sizeof(GIFFrame));
    memset(frame, 0, sizeof(GIFFrame));

    SDL_Color* local_colors = NULL;
    if (img->ImageDesc.ColorMap != NULL) {
      local_colors = (SDL_Color*)SDL_malloc(sizeof(SDL_Color)*gif->SColorMap->ColorCount);
    }

    frames_[f] = frame;
    frame->width_ = img->ImageDesc.Width;
    frame->height_ = img->ImageDesc.Height;

    // TODO: transparency
    Uint8 disposal_method;
    bool is_transparent;
    for(int b = 0; b < img->ExtensionBlockCount; b++) {
      if(img->ExtensionBlocks[b].Function == GRAPHICS_EXT_FUNC_CODE) {
        Uint8 block[4];
        memcpy(block, img->ExtensionBlocks[b].Bytes, 4);
      
        // Check for transparency
        if (block[0] & 0x01)
          is_transparent = true;
        
        // Disposal mode
        disposal_method = block[0] >> 2 << 2;
      }
    }
    frame->surface_ = createSurface(frame->width_, frame->height_);
    
    SDL_Color* color_src = (local_colors == NULL) ? global_colors : local_colors;
    int total_pixels = frame->width_ * frame->height_;

    for (int p = 0; p < total_pixels; p++) {
      SDL_Color c = color_src[img->RasterBits[p]];
      // if (is_transparent) c.a = 0;
      if (f > 0 && (disposal_method & 0x08) != 0x08) {
        setPixel(frames_[f-1]->surface_, frame->surface_, p%frame->width_, p/frame->width_);
      } else {
        setPixel(frame->surface_, p%frame->width_, p/frame->width_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
      }
    }

    frame->texture_ = window->loadTexture(frame->surface_);
    free(local_colors);
  }
  free(global_colors);
  DGifCloseFile(gif, &error);
}

SDL_Surface* GIFImage::createSurface(int width, int height) {
  return SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
}

void GIFImage::setPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
  SDL_Rect rect; rect.x = x; rect.y = y; rect.w = 1; rect.h = 1;
  SDL_FillRect(surface, &rect, color);
}

void GIFImage::setPixel(SDL_Surface* src, SDL_Surface* dst, int x, int y) {
  SDL_Rect rect; rect.x = x; rect.y = y; rect.w = 1; rect.h = 1;
  SDL_BlitSurface(src, &rect, dst, &rect);
}

void GIFImage::setFrameNumber(int frame_num) {
  frame_num_ = frame_num;
}

int GIFImage::getFrameNumber() {
  return frame_num_;
}

int GIFImage::getTotalFrames() {
  return total_frames_;
}

SDL_Texture* GIFImage::getTexture() {
  return frames_[frame_num_]->texture_;
}

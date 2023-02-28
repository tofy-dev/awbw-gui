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

#define GIF_WIPE_SCREEN 2

GIFImage::~GIFImage() {
  for (int f = 0; f < total_frames_; f++) {
    GIFFrame* frame = frames_[f];
    SDL_FreeSurface(frame->surface_);
    SDL_DestroyTexture(frame->texture_);
  }
  std::cout << "deallocate gif" << '\n';
}

GIFImage::GIFImage(std::string path, double scale, RenderWindow* window) {
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
    int transparent_index;
    for(int b = 0; b < img->ExtensionBlockCount; b++) {
      if(img->ExtensionBlocks[b].Function == GRAPHICS_EXT_FUNC_CODE) {
        Uint8 block[4];
        memcpy(block, img->ExtensionBlocks[b].Bytes, 4);
      
        // Check for transparency
        transparent_index = block[3];
        
        // Disposal mode
        Uint8 disposal_method = block[0] >> 2;
        frame->disposal_method_ = disposal_method;
      }
    }
    frame->surface_ = createSurface(frame->width_, frame->height_);
    
    SDL_Color* color_src = (local_colors == NULL) ? global_colors : local_colors;
    int total_pixels = frame->width_ * frame->height_;

    if (f > 0) std::cout << (int)frames_[f-1]->disposal_method_ << '\n';
    for (int p = 0; p < total_pixels; p++) {
      SDL_Color c = color_src[img->RasterBits[p]];
      // TODO: still doesnt work
      if (transparent_index == img->RasterBits[p]) {
        c.a = 0;
      }

      if (f > 0) {
        if (frames_[f-1]->disposal_method_ != GIF_WIPE_SCREEN)
          setPixel(frames_[f-1]->surface_, frame->surface_, p%frame->width_, p/frame->width_);
        if (c.a != 0)
          setPixel(frame->surface_, p%frame->width_, p/frame->width_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
      } else if (c.a != 0) {
        setPixel(frame->surface_, p%frame->width_, p/frame->width_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
      }
    }

    // updates the width + height to be scaled
    frame->width_ = frame->width_*scale;
    frame->height_ = frame->height_*scale;
    frame->texture_ = window->loadTexture(frame->surface_);
    free(local_colors);
  }
  free(global_colors);
  DGifCloseFile(gif, &error);
}

void GIFImage::setFrameNumber(int frame_num) { frame_num_ = frame_num; }
int GIFImage::getFrameNumber() { return frame_num_; }

GIFFrame* GIFImage::getFrame() { return frames_[frame_num_]; }
int GIFImage::getTotalFrames() { return total_frames_; }
SDL_Texture* GIFImage::getTexture() { return frames_[frame_num_]->texture_; }
SDL_Rect GIFImage::getDims() {
  SDL_Rect r;
  r.x = 0; r.y = 0;
  r.w = getWidth(); r.h = getHeight();
  return r;
}

int GIFImage::getWidth() { return getFrame()->width_; }
int GIFImage::getHeight() { return getFrame()->height_; }

// static functions
SDL_Surface* GIFImage::createSurface(int width, int height) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0,width,height,32,0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
  return surface;
}
void GIFImage::setPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
  SDL_Rect rect; rect.x = x; rect.y = y; rect.w = 1; rect.h = 1;
  SDL_FillRect(surface, &rect, color);
}
void GIFImage::setPixel(SDL_Surface* src, SDL_Surface* dst, int x, int y) {
  SDL_Rect rect; rect.x = x; rect.y = y; rect.w = 1; rect.h = 1;
  SDL_BlitSurface(src, &rect, dst, &rect);
}

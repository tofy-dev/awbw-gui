/*
 * Minimalist implementation of https://github.com/grimfang4/SDL_gifwrap
 */

#pragma once
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <gif_lib.h>
#include <iostream>
#include <string>
#include <cassert>

#define GIF_OVERLAY 1
#define GIF_WIPE 2

// constructors + static functions
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
  max_w_ = gif->SWidth;
  max_h_ = gif->SHeight;

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

    int transparent_index;
    bool is_transparent;
    for(int b = 0; b < img->ExtensionBlockCount; b++) {
      if(img->ExtensionBlocks[b].Function == GRAPHICS_EXT_FUNC_CODE) {
        Uint8 block[4];
        memcpy(block, img->ExtensionBlocks[b].Bytes, 4);
      
        // Check for transparency
        is_transparent = ((uint8_t)(block[0] << 7) >> 7) == 0x01;
        transparent_index = block[3];
        
        // Disposal mode
        Uint8 disposal_method = block[0] >> 2;
        frame->disposal_method_ = disposal_method;
      }
    }

    frame->surface_ = createSurface(max_w_, max_h_);
    frame->raw_w_ = img->ImageDesc.Width;
    frame->raw_h_ = img->ImageDesc.Height;

    // copy old surface if the disposal method is to overlay over
    if (shouldOverlay(f)) {
      SDL_BlitSurface(frames_[f-1]->surface_, NULL, frame->surface_, NULL);
    }
    
    SDL_Color* color_src = (local_colors == NULL) ? global_colors : local_colors;
    int total_pixels = frame->raw_w_ * frame->raw_h_;
    int left_off = img->ImageDesc.Left;
    int top_off = img->ImageDesc.Top;

    for (int p = 0; p < total_pixels; p++) {
      SDL_Color c = color_src[img->RasterBits[p]];
      c.a = (is_transparent && transparent_index == img->RasterBits[p]) ? 0 : 255;
      if (c.a != 0)
        setPixel(frame->surface_, left_off + p%frame->raw_w_, top_off + p/frame->raw_w_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
    }

    frame->texture_ = window->loadTexture(frame->surface_);
    free(local_colors);
  }

  free(global_colors);
  DGifCloseFile(gif, &error);

  max_w_ *= scale;
  max_h_ *= scale;
}

GIFImage* GIFImage::createGIF(std::string path, double scale, RenderWindow* window) {
  GIFImage* image = new GIFImage(path, scale, window);
  return image;
}

void GIFImage::destroyGIF(GIFImage* image) {
  for (int f = 0; f < image->getTotalFrames(); f++) {
    image->setFrameNumber(f);
    SDL_DestroyTexture(image->getFrame()->texture_);
    SDL_FreeSurface(image->getFrame()->surface_);

  }
  delete image;
}

SDL_Surface* GIFImage::createSurface(int width, int height) {
  SDL_Surface* surface = SDL_CreateRGBSurface(0,width,height,32,0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
  SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
  return surface;
}

void GIFImage::setPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
  SDL_Rect rect; rect.x = x; rect.y = y; rect.w = 1; rect.h = 1;
  SDL_FillRect(surface, &rect, color);
}


// getters
bool GIFImage::shouldOverlay(int frame_num) {
  return frame_num > 0 && frames_[frame_num-1]->disposal_method_ == GIF_OVERLAY;
}

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

int GIFImage::getWidth() { return max_w_; }
int GIFImage::getHeight() { return max_h_; }


// setters
void GIFImage::setFrameNumber(int frame_num) { frame_num_ = frame_num; }

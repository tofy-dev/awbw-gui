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
// TODO: do gradient eventually
GIFImage::GIFImage(int r, int g, int b, int max_alpha) {
}

GIFImage::GIFImage(std::string path, double scale, int max_alpha, RenderWindow* window) {
  std::cout << "Loading " << path << '\n';

  GifFileType* gif;
  int error = -1;
  gif = DGifOpenFileName(path.c_str(), &error);

  assert(gif != NULL);
  assert(DGifSlurp(gif) != GIF_ERROR);

  SDL_Color* global_colors = NULL;
  if (gif->SColorMap != NULL) {
    global_colors = (SDL_Color*)SDL_malloc(sizeof(SDL_Color)*gif->SColorMap->ColorCount);
    for (int i = 0; i < gif->SColorMap->ColorCount; i++) {
      global_colors[i].r = gif->SColorMap->Colors[i].Red;
      global_colors[i].g = gif->SColorMap->Colors[i].Green;
      global_colors[i].b = gif->SColorMap->Colors[i].Blue;
      global_colors[i].a = 255;
    }
  }

  total_frames_ = gif->ImageCount;
  frame_num_ = 0;
  max_w_ = gif->SWidth;
  max_h_ = gif->SHeight;

  std::cout << "DIMS: " << max_w_ << "x" << max_h_ << '\n';
  std::cout << "FRAMES: " << gif->ImageCount << '\n';

  frames_ = std::vector<GIFFrame*>(gif->ImageCount);
  for (int f = 0; f < gif->ImageCount; f++) {
    std::cout << "START FRAME " << f << '\n';
    SavedImage* img = &gif->SavedImages[f];
    GIFFrame* frame = new GIFFrame();

    std::cout << "LOAD LOCAL COLORS" << '\n';
    SDL_Color* local_colors = NULL;
    if (img->ImageDesc.ColorMap != NULL) {
      local_colors = (SDL_Color*)SDL_malloc(sizeof(SDL_Color)*img->ImageDesc.ColorMap->ColorCount);
      for (int i = 0; i < img->ImageDesc.ColorMap->ColorCount; i++) {
        local_colors[i].r = img->ImageDesc.ColorMap->Colors[i].Red;
        local_colors[i].g = img->ImageDesc.ColorMap->Colors[i].Green;
        local_colors[i].b = img->ImageDesc.ColorMap->Colors[i].Blue;
        local_colors[i].a = 255;
      }
      if (path == "res/assets/custom/blue.gif")
        std::cout << "CC: " << img->ImageDesc.ColorMap->ColorCount << '\n';
    }
    frames_[f] = frame;

    std::cout << "SET TRANSPARENCY" << '\n';
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

        // Find delay (in hundreths of seconds)
        // note: this ignores block two
        frame->delay_ = block[1]*10;
      }
    }

    std::cout << "GENERATE SURFACE" << '\n';
    frame->surface_ = createSurface(max_w_, max_h_);
    frame->raw_w_ = img->ImageDesc.Width;
    frame->raw_h_ = img->ImageDesc.Height;

    // copy old surface if the disposal method is to overlay over
    if (shouldOverlay(f)) {
      SDL_BlitSurface(frames_[f-1]->surface_, NULL, frame->surface_, NULL);
    }
    
    SDL_Color* color_src = (local_colors == NULL) ? global_colors : local_colors;
    assert(color_src != NULL);

    int total_pixels = frame->raw_w_ * frame->raw_h_;
    int left_off = img->ImageDesc.Left;
    int top_off = img->ImageDesc.Top;

    for (int p = 0; p < total_pixels; p++) {
      // TODO: make not temporary
      if (path == "res/assets/custom/blue.gif")
        std::cout << "RB: " << (int)img->RasterBits[p] << '\n';
      SDL_Color c = color_src[img->RasterBits[p]];
      c.a = (is_transparent && transparent_index == img->RasterBits[p]) ? 0 : max_alpha;
      if (c.a != 0)
        setPixel(frame->surface_, left_off + p%frame->raw_w_, top_off + p/frame->raw_w_, SDL_MapRGBA(frame->surface_->format, c.r, c.g, c.b, c.a));
    }

    frame->texture_ = window->loadTexture(frame->surface_);
    std::cout << "FREE local_colors\n";
    if (local_colors != NULL) SDL_free(local_colors);
  }

  std::cout << "FREE global_colors\n";
  if (global_colors != NULL) SDL_free(global_colors);

  std::cout << "CLOSE FILE\n";
  DGifCloseFile(gif, &error);

  max_w_ *= scale;
  max_h_ *= scale;
  
  std::cout << "Finished loading gif.\n";
}

GIFImage* GIFImage::createGIF(std::string path, double scale, RenderWindow* window) {
  return createGIF(path, scale, 255, window);
}
GIFImage* GIFImage::createGIF(std::string path, double scale, int max_alpha, RenderWindow* window) {
  return new GIFImage(path, scale, max_alpha, window);
}

// TODO: maybe redo to put destroyers in frame destructor
void GIFImage::destroyGIF(GIFImage* image) {
  std::cout << "gif destroyed\n";
  for (int f = 0; f < image->getTotalFrames(); f++) {
    image->setFrameNumber(f);
    SDL_DestroyTexture(image->getFrame()->texture_);
    SDL_FreeSurface(image->getFrame()->surface_);
    delete image->getFrame();
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

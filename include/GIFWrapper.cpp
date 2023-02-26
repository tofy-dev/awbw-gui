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
  file_ = DGifOpenFileName(path.c_str(), &error_);
  assert(file_ != NULL);
  if (DGifSlurp(file_) != GIF_OK) {
    DGifCloseFile(file_, &error_);
    std::cout << "Failed to slurp file " << path << ".\n";
  } else {
    width_ = file_->SWidth;
    height_ = file_->SHeight;
    std::cout << "Sets width, height\n";

    // Generate palette
    global_palette_ = SDL_AllocPalette(file_->SColorMap->ColorCount);
    std::cout << "Creates palette of size " << file_->SColorMap->ColorCount << "\n";
    createPalette(global_palette_, file_->SColorMap);
    std::cout << "Creates palettes\n";

    // Do frames
    total_frames_ = file_->ImageCount;
    frames_ = std::vector<GIFFrame*>(total_frames_);
    std::cout << "Creates " << total_frames_ << " frames\n";
    for (int i = 0; i < total_frames_; i++) {
      std::cout << i << "\n";
      SavedImage* img = &file_->SavedImages[i];
      GIFFrame* frame = (GIFFrame*)SDL_malloc(sizeof(GIFFrame));
      memset(frame, 0, sizeof(GIFFrame));
      std::cout << "Checkpoint A\n";

      frames_[i] = frame;
      frame->width_ = 30;
      frame->width_ = img->ImageDesc.Width;
      frame->height_ = img->ImageDesc.Height;
      frame->left_off_ = img->ImageDesc.Left;
      frame->top_off_ = img->ImageDesc.Top;
      std::cout << "Checkpoint B\n";
      
      SDL_Palette* local_palette = NULL;
      if (img->ImageDesc.ColorMap != NULL) {
        local_palette = SDL_AllocPalette(img->ImageDesc.ColorMap->ColorCount);
        createPalette(local_palette, img->ImageDesc.ColorMap);
        frame->setPalette(local_palette);
      }
      std::cout << "Checkpoint C\n";

      SDL_Palette* temp_pal = (local_palette == NULL) ? global_palette_ : local_palette;
      for (int j = 0; j < img->ExtensionBlockCount; j++) {
        if (img->ExtensionBlocks[j].Function == GRAPHICS_EXT_FUNC_CODE) {
          Uint8 block[4];
          memcpy(block, img->ExtensionBlocks[j].Bytes, 4); 
          
          if (block[0] & 0x01)
            frame->transparent_ = true;
          frame->trans_idx_ = block[3];

          if (temp_pal != NULL && frame->trans_idx_ < temp_pal->ncolors)
            frame->transparent_color_ = temp_pal->colors[frame->trans_idx_];
        }
      }
      std::cout << "Checkpoint D\n";

      // Create surface
      int count = img->ImageDesc.Width * img->ImageDesc.Height;
      frame->setSurface(createSurface(frame->width_, frame->height_));
      frame->has_surface_ = SDL_TRUE;
      std::cout << "Checkpoint E\n";

      if (temp_pal != NULL) {
        for (int j = 0; j < count; j++) {
          SDL_Color c = temp_pal->colors[img->RasterBits[j]];
          if (frame->trans_idx_ == img->RasterBits[j])
            c.a = 0;
          setPixel(frame->getSurface(), j%frame->width_, j/frame->width_, SDL_MapRGBA(frame->getSurface()->format, c.r, c.g, c.b, c.a));
        }
      }
      std::cout << "Checkpoint F\n";
    }

    DGifCloseFile(file_, &error_);
  }
  std::cout << "done!\n";
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

void GIFImage::createPalette(SDL_Palette* palette, ColorMapObject* map) {
  for (int i = 0; i < map->ColorCount; i++) {
    palette->colors[i].r = map->Colors->Red;
    palette->colors[i].g = map->Colors->Green;
    palette->colors[i].b = map->Colors->Blue;
    palette->colors[i].a = 255;
  }
}

SDL_Surface* GIFImage::createSurface(int width, int height)
{
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    else
        return SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
}

void GIFImage::setPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
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

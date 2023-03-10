#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow {
public:
  RenderWindow(const char* p_title, int p_w, int p_h);
  ~RenderWindow();

  SDL_Texture* loadTexture(const char* p_filePath);
  SDL_Texture* loadTexture(SDL_Surface* p_surface);

  void clear();
  void render(SDL_Texture* p_tex);
  void render(SDL_Texture* p_tex, SDL_Rect p_dst);
  void display();
  void setSize(int w, int h);

private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

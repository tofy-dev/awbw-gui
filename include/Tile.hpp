#pragma once
#include "RenderWindow.hpp"
#include <array>
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class Tile {
public:
  Tile(int id, RenderWindow* window);
  int getId();
  void onClick();

  bool isActive();
  std::array<int, 2> getDims(int basic);
  std::string getName();
  SDL_Texture* getTexture();

private:
  int id_;
  bool active_;
  SDL_Texture* texture_;
  RenderWindow* window_;

  static inline const std::array<std::string,195> terrain_list_ = {"","Plain","Mountain","Wood","HRiver","VRiver","CRiver","ESRiver","SWRiver","WNRiver","NERiver","ESWRiver","SWNRiver","WNERiver","NESRiver","HRoad","VRoad","CRoad","ESRoad","SWRoad","WNRoad","NERoad","ESWRoad","SWNRoad","WNERoad","NESRoad","HBridge","VBridge","Sea","HShoal","HShoalN","VShoal","VShoalE","Reef","Neutral City","Neutral Base","Neutral Airport","Neutral Port","Orange Star City","Orange Star Base","Orange Star Airport","Orange Star Port","Orange Star HQ","Blue Moon City","Blue Moon Base","Blue Moon Airport","Blue Moon Port","Blue Moon HQ","Green Earth City","Green Earth Base","Green Earth Airport","Green Earth Port","Green Earth HQ","Yellow Comet City","Yellow Comet Base","Yellow Comet Airport","Yellow Comet Port","Yellow Comet HQ","","","","","","","","","","","","","","","","","","","","","","","","Red Fire City","Red Fire Base","Red Fire Airport","Red Fire Port","Red Fire HQ","Grey Sky City","Grey Sky Base","Grey Sky Airport","Grey Sky Port","Grey Sky HQ","Black Hole City","Black Hole Base","Black Hole Airport","Black Hole Port","Black Hole HQ","Brown Desert City","Brown Desert Base","Brown Desert Airport","Brown Desert Port","Brown Desert HQ","VPipe","HPipe","NEPipe","ESPipe","SWPipe","WNPipe","NPipe End","EPipe End","SPipe End","WPipe End","Missile Silo","Missile Silo Empty","HPipe Seam","VPipe Seam","HPipe Rubble","VPipe Rubble","Amber Blaze Airport","Amber Blaze Base","Amber Blaze City","Amber Blaze HQ","Amber Blaze Port","Jade Sun Airport","Jade Sun Base","Jade Sun City","Jade Sun HQ","Jade Sun Port","Amber Blaze Com Tower","Black Hole Com Tower","Blue Moon Com Tower","Brown Desert Com Tower","Green Earth Com Tower","Jade Sun Com Tower","Neutral Com Tower","Orange Star Com Tower","Red Fire Com Tower","Yellow Comet Com Tower","Grey Sky Com Tower","Amber Blaze Lab","Black Hole Lab","Blue Moon Lab","Brown Desert Lab","Green Earth Lab","Grey Sky Lab","Jade Sun Lab","Neutral Lab","Orange Star Lab","Red Fire Lab","Yellow Comet Lab","Cobalt Ice Airport","Cobalt Ice Base","Cobalt Ice City","Cobalt Ice Com Tower","Cobalt Ice HQ","Cobalt Ice Lab","Cobalt Ice Port","Pink Cosmos Airport","Pink Cosmos Base","Pink Cosmos City","Pink Cosmos Com Tower","Pink Cosmos HQ","Pink Cosmos Lab","Pink Cosmos Port","Teal Galaxy Airport","Teal Galaxy Base","Teal Galaxy City","Teal Galaxy Com Tower","Teal Galaxy HQ","Teal Galaxy Lab","Teal Galaxy Port","Purple Lightning Airport","Purple Lightning Base","Purple Lightning City","Purple Lightning Com Tower","Purple Lightning HQ","Purple Lightning Lab","Purple Lightning Port","","","","","Acid Rain Airport","Acid Rain Base","Acid Rain City","Acid Rain Com Tower","Acid Rain HQ","Acid Rain Lab","Acid Rain Port","White Nova Airport","White Nova Base","White Nova City","White Nova Com Tower","White Nova HQ","White Nova Lab","White Nova Port"};
};

#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <memory>
#include <string>
#include <optional>
#include "GIFWrapper.hpp"
#include "RenderWindow.hpp"
#include "Unit.hpp"

#define TILE_NONE 0
#define TILE_HIGHLIGHT 1

class Tile {
public:
  Tile(int id, RenderWindow* window);
  virtual ~Tile() = default;

  static Tile* createTile(int id, RenderWindow* window);
  static void destroyTile(Tile* tile);

  static std::string getName(int id);
  static void setScaling(double scaling);

  virtual void onClick() = 0;

  int getId();
  Unit* getUnit();
  GIFImage* getGIF();

  void setUnit(Unit* unit);
  void setUnit(Unit* unit, bool destroy);

protected:
  int state = TILE_NONE;
  Unit* unit_ = nullptr;

  int id_;
  int h_mult_ = 16;

  GIFImage* gif_;
  RenderWindow* window_;

  static inline const std::array<std::string,195> terrain_list_ = {"","Plain","Mountain","Wood","HRiver","VRiver","CRiver","ESRiver","SWRiver","WNRiver","NERiver","ESWRiver","SWNRiver","WNERiver","NESRiver","HRoad","VRoad","CRoad","ESRoad","SWRoad","WNRoad","NERoad","ESWRoad","SWNRoad","WNERoad","NESRoad","HBridge","VBridge","Sea","HShoal","HShoalN","VShoal","VShoalE","Reef","Neutral City","Neutral Base","Neutral Airport","Neutral Port","Orange Star City","Orange Star Base","Orange Star Airport","Orange Star Port","Orange Star HQ","Blue Moon City","Blue Moon Base","Blue Moon Airport","Blue Moon Port","Blue Moon HQ","Green Earth City","Green Earth Base","Green Earth Airport","Green Earth Port","Green Earth HQ","Yellow Comet City","Yellow Comet Base","Yellow Comet Airport","Yellow Comet Port","Yellow Comet HQ","","","","","","","","","","","","","","","","","","","","","","","","Red Fire City","Red Fire Base","Red Fire Airport","Red Fire Port","Red Fire HQ","Grey Sky City","Grey Sky Base","Grey Sky Airport","Grey Sky Port","Grey Sky HQ","Black Hole City","Black Hole Base","Black Hole Airport","Black Hole Port","Black Hole HQ","Brown Desert City","Brown Desert Base","Brown Desert Airport","Brown Desert Port","Brown Desert HQ","VPipe","HPipe","NEPipe","ESPipe","SWPipe","WNPipe","NPipe End","EPipe End","SPipe End","WPipe End","Missile Silo","Missile Silo Empty","HPipe Seam","VPipe Seam","HPipe Rubble","VPipe Rubble","Amber Blaze Airport","Amber Blaze Base","Amber Blaze City","Amber Blaze HQ","Amber Blaze Port","Jade Sun Airport","Jade Sun Base","Jade Sun City","Jade Sun HQ","Jade Sun Port","Amber Blaze Com Tower","Black Hole Com Tower","Blue Moon Com Tower","Brown Desert Com Tower","Green Earth Com Tower","Jade Sun Com Tower","Neutral Com Tower","Orange Star Com Tower","Red Fire Com Tower","Yellow Comet Com Tower","Grey Sky Com Tower","Amber Blaze Lab","Black Hole Lab","Blue Moon Lab","Brown Desert Lab","Green Earth Lab","Grey Sky Lab","Jade Sun Lab","Neutral Lab","Orange Star Lab","Red Fire Lab","Yellow Comet Lab","Cobalt Ice Airport","Cobalt Ice Base","Cobalt Ice City","Cobalt Ice Com Tower","Cobalt Ice HQ","Cobalt Ice Lab","Cobalt Ice Port","Pink Cosmos Airport","Pink Cosmos Base","Pink Cosmos City","Pink Cosmos Com Tower","Pink Cosmos HQ","Pink Cosmos Lab","Pink Cosmos Port","Teal Galaxy Airport","Teal Galaxy Base","Teal Galaxy City","Teal Galaxy Com Tower","Teal Galaxy HQ","Teal Galaxy Lab","Teal Galaxy Port","Purple Lightning Airport","Purple Lightning Base","Purple Lightning City","Purple Lightning Com Tower","Purple Lightning HQ","Purple Lightning Lab","Purple Lightning Port","","","","","Acid Rain Airport","Acid Rain Base","Acid Rain City","Acid Rain Com Tower","Acid Rain HQ","Acid Rain Lab","Acid Rain Port","White Nova Airport","White Nova Base","White Nova City","White Nova Com Tower","White Nova HQ","White Nova Lab","White Nova Port"};
  static inline double scaling_ = 1;
};

class City : public Tile {
public:
  City(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 22;};
  ~City();
  void onClick() override;
};

class Base: public Tile {
public:
  Base(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 25;};
  ~Base();
  void onClick() override;
};

class Airport : public Tile {
public:
  Airport(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 18;};
  ~Airport();
  void onClick() override;
};

class Port : public Tile {
public:
  Port(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 22;};
  ~Port();
  void onClick() override;
};

class HQ : public Tile {
public:
  HQ(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 31;};
  ~HQ();
  void onClick() override;
};

class Lab : public Tile {
public:
  Lab(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 24;};
  ~Lab();
  void onClick() override;
};

class ComTower : public Tile {
public:
  ComTower(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 25;};
  ~ComTower();
  void onClick() override;
};

class Mountain: public Tile {
public:
  ~Mountain();
  Mountain(int id, RenderWindow* window) : Tile(id, window) {h_mult_ = 21;};
  void onClick() override;
};

class Terrain : public Tile {
public:
  ~Terrain();
  Terrain(int id, RenderWindow* window) : Tile(id, window) {};
  void onClick() override;
};

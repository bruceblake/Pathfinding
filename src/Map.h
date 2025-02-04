#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <vector>
using std::vector;

class Map {
public:
  Map();
  void LoadMap(vector<vector<int>> arr);
  void DrawMap();

  // The maze layout (a 20×25 grid).
  vector<vector<int>> map = vector<vector<int>>(40, vector<int>(25, 0));

private:
  SDL_Texture *dirt;
  SDL_Texture *grass;
  SDL_Texture *water;
  SDL_Rect src, dest;
};

#endif

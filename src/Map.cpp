#include "Map.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
using std::vector;

// Maze definition: 0 = wall (water), 1 = open (grass)
// (In this example, only 0 and 1 are used. You could add additional tile
// types.)
vector<vector<int>> lvl1 = {
    // Row 0 (Top border with an entrance at col 1)
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    // Row 1
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0},

    // Row 2
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},

    // Row 3
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 4
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},

    // Row 5
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 6
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},

    // Row 7
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},

    // Row 8
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},

    // Row 9
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 10
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},

    // Row 11
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 12
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},

    // Row 13
    {0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},

    // Row 14
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},

    // Row 15
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 16
    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},

    // Row 17
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},

    // Row 18
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},

    // Row 19 (Bottom border with an exit at col 23)
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};
Map::Map() {
  // Load tile textures (update these paths as needed)
  dirt = TextureManager::LoadTexture(
      "/home/thomasanderson/my_sdl/assets/dirt.png");
  grass = TextureManager::LoadTexture(
      "/home/thomasanderson/my_sdl/assets/grass.png");
  water = TextureManager::LoadTexture(
      "/home/thomasanderson/my_sdl/assets/water.png");

  LoadMap(lvl1);

  src.x = src.y = 0;
  src.w = dest.w = 32;
  src.h = dest.h = 32;
  dest.x = dest.y = 0;
}

void Map::LoadMap(vector<vector<int>> arr) {
  for (int row = 0; row < 40; row++) {
    for (int col = 0; col < 25; col++) {
      map[row][col] = arr[row][col];
    }
  }
}

void Map::DrawMap() {
  int type = 0;
  for (int row = 0; row < 40; row++) {
    for (int col = 0; col < 25; col++) {
      type = map[row][col];
      dest.x = col * 32;
      dest.y = row * 32;
      switch (type) {
      case 0:
        TextureManager::Draw(water, src, dest);
        break;
      case 1:
        TextureManager::Draw(grass, src, dest);
        break;
      case 2:
        TextureManager::Draw(dirt, src, dest);
        break;
      default:
        break;
      }
    }
  }
}

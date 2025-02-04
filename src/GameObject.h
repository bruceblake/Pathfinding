#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

class GameObject {
public:
  GameObject(const char *texturesheet, int x, int y);
  void Update();
  void Render();
  void SetPosition(int x, int y);

private:
  int xPos, yPos;
  SDL_Texture *objTexture;
  SDL_Rect srcRect, destRect;
};

#endif


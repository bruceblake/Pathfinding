#include "GameObject.h"
#include "Game.h" // For access to Game::renderer
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <iostream>

GameObject::GameObject(const char *texturesheet, int x, int y) {
  objTexture = TextureManager::LoadTexture(texturesheet);
  xPos = x;
  yPos = y;
}

void GameObject::SetPosition(int x, int y) {
  xPos = x;
  yPos = y;
  destRect.x = xPos;
  destRect.y = yPos;
  std::cout << "SetPosition: x = " << xPos << ", y = " << yPos << std::endl;
}

void GameObject::Update() {
  // Define the source rectangle (assumes the sprite sheet begins at (0,0))
  srcRect.h = 32;
  srcRect.w = 32;
  srcRect.x = 0;
  srcRect.y = 0;

  // Define the destination rectangle (where and how big to draw the sprite)
  destRect.x = xPos;
  destRect.y = yPos;
  destRect.w = 32;
  destRect.h = 32;
}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

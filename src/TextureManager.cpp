#include "TextureManager.h"
#include "Game.h" // For access to Game::renderer
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
  SDL_Surface *tempSurface = IMG_Load(fileName);
  if (tempSurface == nullptr) {
    std::cerr << "Failed to load image: " << fileName
              << "\nIMG_Error: " << IMG_GetError() << std::endl;
    return nullptr; // Return early to avoid using a null surface.
  }
  SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
  if (tex == nullptr) {
    std::cerr << "Failed to create texture from: " << fileName
              << "\nSDL_Error: " << SDL_GetError() << std::endl;
  }
  SDL_FreeSurface(tempSurface);
  return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

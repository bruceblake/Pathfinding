#include "Game.h"
#include <SDL2/SDL.h>
#include <string>

Game *game = nullptr;

int main(int argc, char *argv[]) {
  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  bool showPath = false;
  if (argc > 1) {
    std::string arg = argv[1];
    if (arg == "show") {
      showPath = true;
    }
  }

  game = new Game();
  game->init("Maze Traversal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             800, 600, false, showPath);

  while (game->running()) {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game->clean();
  delete game;

  return 0;
}

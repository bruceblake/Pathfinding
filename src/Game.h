#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
using std::pair;
using std::vector;

class Game {
public:
  Game();
  ~Game();

  void init(const char *title, int xPos, int yPos, int width, int height,
            bool fullscreen, bool showPath);
  void handleEvents();
  void update();
  void render();
  void clean();
  bool running() { return isRunning; }

  // Dijkstra’s algorithm to compute the shortest path in the maze.
  vector<pair<int, int>> dijkstra(const vector<vector<int>> &maze,
                                  pair<int, int> start, pair<int, int> goal);
  bool isValid(int x, int y, const vector<vector<int>> &maze);

  // The computed path (in maze grid coordinates) and a pointer to the current
  // step.
  vector<pair<int, int>> path;
  int currentPathIndex = 0;

  // Make the renderer accessible to other parts of the program.
  static SDL_Renderer *renderer;

private:
  SDL_Window *window = nullptr;
  bool isRunning = false;
  bool showPath = false;
};

#endif

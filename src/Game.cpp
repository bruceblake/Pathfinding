#include "Game.h"
#include "GameObject.h"
#include "Map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Global pointers for our player and the map (for simplicity)
GameObject *player = nullptr;
Map *map = nullptr;

SDL_Renderer *Game::renderer = nullptr;

// Maze dimensions (must match the dimensions used in Map)
const int ROWS = 40;
const int COLS = 25;

// Directions for movement: up, down, left, right.
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xPos, int yPos, int width, int height,
                bool fullscreen, bool showPath) {
  int flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  this->showPath = showPath;

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialised!\n";
    window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
    if (window) {
      std::cout << "Window created!\n";
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      std::cout << "Renderer created!\n";
    }

    // Initialize SDL_image (ensure JPG and PNG support)
    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) &
          (IMG_INIT_JPG | IMG_INIT_PNG))) {
      std::cerr << "SDL_image could not initialize! Error: " << IMG_GetError()
                << "\n";
      isRunning = false;
      return;
    }

    isRunning = true;
  } else {
    isRunning = false;
  }

  // Create our player and maze map objects.
  // (The player texture is loaded from a JPG image.)
  player =
      new GameObject("/home/thomasanderson/my_sdl/assets/player.png", 0, 0);
  map = new Map();

  // Define start and goal positions (choose valid walkable tiles)
  pair<int, int> start = {0, 1};  // row 0, col 0 (if walkable)
  pair<int, int> goal = {19, 23}; // row 19, col 24 (if walkable)

  path = dijkstra(map->map, start, goal);
  std::cout << "Computed path length: " << path.size() << std::endl;
  for (auto cell : path) {
    std::cout << "(" << cell.first << ", " << cell.second << ") ";
  }
  std::cout << std::endl;

  currentPathIndex = 0;
  if (!path.empty()) {
    // Convert maze coordinates: (col, row) for screen coordinates.
    player->SetPosition(path[0].second * 32, path[0].first * 32);
  }
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  case SDL_KEYDOWN:
    // You can add keyboard controls here if desired.
    break;
  default:
    break;
  }
}

void Game::update() {
  static int frameCounter = 0;
  frameCounter++;
  if (frameCounter % 10 == 0 &&
      currentPathIndex < static_cast<int>(path.size()) - 1) {
    currentPathIndex++;
    int newX = path[currentPathIndex].second * 32; // column -> x
    int newY = path[currentPathIndex].first * 32;  // row -> y
    player->SetPosition(newX, newY);
    std::cout << "Moving to: (" << newX << ", " << newY << ")\n";
  }
  player->Update();
}

void Game::render() {
  SDL_RenderClear(renderer);

  // Draw the maze.
  map->DrawMap();

  if (showPath) {
    // (Optional) Draw the computed path in green.
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto p : path) {
      SDL_Rect rect = {p.second * 32, p.first * 32, 32, 32};
      SDL_RenderFillRect(renderer, &rect);
    }
  }

  // Render the player sprite.
  player->Render();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  IMG_Quit();
  SDL_Quit();
  std::cout << "Game Cleaned\n";
}

// Dijkstra’s Algorithm Implementation
vector<pair<int, int>> Game::dijkstra(const vector<vector<int>> &maze,
                                      pair<int, int> start,
                                      pair<int, int> goal) {
  vector<vector<int>> dist(ROWS, vector<int>(COLS, INT_MAX));
  dist[start.first][start.second] = 0;

  // Priority queue stores (distance, (x, y))
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                 greater<pair<int, pair<int, int>>>>
      pq;
  pq.push({0, start});

  // To reconstruct the path.
  vector<vector<pair<int, int>>> parent(ROWS,
                                        vector<pair<int, int>>(COLS, {-1, -1}));

  while (!pq.empty()) {
    int currentDist = pq.top().first;
    int x = pq.top().second.first;
    int y = pq.top().second.second;
    pq.pop();

    if (x == goal.first && y == goal.second) {
      break;
    }

    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (isValid(nx, ny, maze)) {
        int newDist = currentDist + 1;
        if (newDist < dist[nx][ny]) {
          dist[nx][ny] = newDist;
          pq.push({newDist, {nx, ny}});
          parent[nx][ny] = {x, y};
        }
      }
    }
  }

  vector<pair<int, int>> path;
  if (dist[goal.first][goal.second] != INT_MAX) {
    pair<int, int> current = goal;
    while (current != start) {
      path.push_back(current);
      current = parent[current.first][current.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
  }

  return path;
}

bool Game::isValid(int x, int y, const vector<vector<int>> &maze) {
  return x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] != 0;
}

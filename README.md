# Maze Traversal Project

This project is a simple 2D maze traversal game built using SDL2. The game demonstrates how to load a maze from a grid, compute the shortest path from an entrance to an exit using Dijkstra’s algorithm, and animate a player sprite following that path.

## Features

- **Maze Rendering:**  
  Displays a maze defined as a grid where 0 represents walls and 1 represents walkable cells.

- **Pathfinding:**  
  Implements Dijkstra’s algorithm to compute the shortest path from a specified start cell to an exit cell.

- **Player Movement:**  
  A player sprite moves along the computed path.

- **Command-Line Options:**  
  Supports command-line arguments (e.g., toggling fullscreen mode, selecting a maze file).

## Dependencies

- **SDL2:**  
  - [SDL2](https://www.libsdl.org/)
- **SDL2_image:**  
  - [SDL2_image](https://www.libsdl.org/projects/SDL_image/)

Ensure that you have the SDL2 and SDL2_image development libraries installed on your system.

## Building the Project

This project uses CMake for building. Follow these steps to build:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/maze-traversal.git
   cd maze-traversal
Create a Build Directory and Run CMake:

bash
Copy
mkdir build
cd build
cmake ..
Build the Project:

bash
Copy
make
This will produce an executable (e.g., MazeTraversal).

Running the Project
Once built, you can run the executable from the build directory. The program accepts command-line arguments to modify its behavior.

Basic Usage
bash
Copy
./MazeTraversal
Command-Line Options
--fullscreen
Runs the game in fullscreen mode.

--maze <file>
Specifies a maze file to load. (The default maze is embedded in the code.)

show
An example argument that may trigger a debug or special mode.

Example:

bash
Copy
./MazeTraversal --fullscreen --maze myMaze.txt
Project Structure
main.cpp:
Contains the main() function, processes command-line arguments, and starts the game loop.

Game.h/Game.cpp:
Implements the core game logic, including initialization, event handling, updating, and rendering. Also contains the Dijkstra algorithm for pathfinding.

GameObject.h/GameObject.cpp:
Implements the player (or other entities) that are rendered on screen.

Map.h/Map.cpp:
Implements the maze map and rendering logic. The maze is defined as a 2D vector (grid) of integers.

TextureManager.h/TextureManager.cpp:
Provides helper functions for loading textures from image files and drawing them on screen.

CMakeLists.txt:
The CMake build script for configuring the project.

Maze Details
The default maze is defined in the source code as a grid. For example, one version of the maze is a 40 × 25 grid with a single entrance and exit:

Entrance: Row 0, Column 1
Exit: Row 39, Column 23
Feel free to modify the maze layout in Map.cpp to experiment with different maze designs.

Troubleshooting
Missing Textures:
Make sure the asset paths in the code (e.g., for the player sprite and tile textures) are correct and that the image files are present.

Linking Errors:
Verify that SDL2 and SDL2_image are properly installed and that CMake finds them using pkg-config.

Runtime Errors:
Use debugging messages printed to the console to help diagnose issues with maze loading or player movement.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgements
SDL2 and SDL2_image libraries for providing the framework for multimedia and image handling.
Community tutorials and documentation for guidance on implementing Dijkstra's algorithm and game loops.

# Specify the minimum CMake version and the project details.
cmake_minimum_required(VERSION 3.10)
project(MySDL2Project VERSION 1.0 LANGUAGES CXX)

# Optionally set the C++ standard.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pkg-config, which helps locate libraries like SDL2 and SDL2_image.
find_package(PkgConfig REQUIRED)

# Use pkg-config to find SDL2 and SDL2_image.
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Create the executable target from your source file(s).
add_executable(main src/main.cpp src/Game.cpp src/Game.h assets/download.jpg src/TextureManager.cpp src/TextureManager.h src/GameObject.cpp src/GameObject.h src/Map.h src/Map.cpp)
# Specify include directories for SDL2 and SDL2_image.
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
# Link the SDL2 and SDL2_image libraries to your executable.
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
# (Optional) Display SDL2 and SDL2_image compile and link flags for debugging:
message(STATUS "SDL2 Include Dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 Libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_IMAGE Include Dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_IMAGE Libraries: ${SDL2_IMAGE_LIBRARIES}")

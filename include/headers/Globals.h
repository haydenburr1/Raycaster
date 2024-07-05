#pragma once
#include <array>

#define FLAT 0

extern const int WIDTH;
extern const int HEIGHT;
extern const int GRID_SIZE;

// Declarations for MAP_WIDTH and MAP_HEIGHT
extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

// Declare the map after the dimensions have been defined
extern const std::array<std::array<int, 15>, 9>  LEVEL_1;
extern const std::array<std::array<int, 15>, 9>  LEVEL_2;

extern std::array<std::array<int, 15>, 9> map;

extern const float PI;



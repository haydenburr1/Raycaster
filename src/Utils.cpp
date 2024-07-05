#include "headers/Utils.h"

bool Utils::checkRayCollisions(const sf::Vector2f& rayPos)
{
    int gridX = static_cast<int>(rayPos.x / GRID_SIZE);
    int gridY = static_cast<int>(rayPos.y / GRID_SIZE);

    if (gridX < 0 || gridY < 0 || gridX >= MAP_WIDTH || gridY >= MAP_HEIGHT) {
        return true;
    }

    return map[gridY][gridX] == 1;
}

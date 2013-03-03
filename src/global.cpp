#include "global.h"

sf::Vector2i gridPosition(sf::Vector2i i)
{
    const int gridSize = 41; //grid box + border
    return {(i.x - gridSize) / gridSize, (i.y - 1) / gridSize};
}

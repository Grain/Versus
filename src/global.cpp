#include "global.h"

sf::Vector2i gridPosition(sf::Vector2i i)
{
    const int gridSize = BOXDIMENSIONS + 1; //grid box + border

    if((i.x - gridSize) < 0)    //without this, clicks at positions like 5, 5 will return 0, 0, when it SHOULD technically be -0, 0
    {
        return {-1, 0};
    }
    return {(i.x - gridSize) / gridSize, (i.y - 1) / gridSize};
}

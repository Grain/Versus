#include "global.h"

sf::Vector2i gridPosition(sf::Vector2i i)
{
    const int gridSize = BOXDIMENSIONS + 1; //grid box + border

    if(i.x - gridSize < 0)    //without this, clicks at positions like 5, 5 will return 0, 0, when it SHOULD technically be -0, 0
    {
        return {-1, 0};
    }
    if(i.y < 0) //same as above
    {
        return {0, -1};
    }
    return {(i.x - gridSize) / gridSize, (i.y - 1) / gridSize};
}

sf::Vector2i coordinatePosition(sf::Vector2i i)
{
    static const int gridSize = BOXDIMENSIONS + 1; //grid box + border

    return {(gridSize + i.x * gridSize), (1 + i.y * gridSize)};
}

double distance(sf::Vector2f a, sf::Vector2f b)
{
    //printf("%f %f %f %f\n", a.x, a.y, b.x, b.y);
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

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

void initializeStats()
{
    //basic 1
    towerStats[0][0][0].cost = 100;
    towerStats[0][0][0].damage = 10;
    towerStats[0][0][0].fireRate = 30;
    towerStats[0][0][0].homing = false;
    towerStats[0][0][0].range = 100;
    towerStats[0][0][0].speed = 4;
    towerStats[0][0][0].type = 0;

    //1.1 lvl 0
    towerStats[0][1][0].cost = 100;
    towerStats[0][1][0].damage = 10;
    towerStats[0][1][0].fireRate = 30;
    towerStats[0][1][0].homing = false;
    towerStats[0][1][0].range = 100;
    towerStats[0][1][0].speed = 4;
    towerStats[0][1][0].type = 1;

    //1.1 lvl 1
    towerStats[0][1][1].cost = 100;
    towerStats[0][1][1].damage = 10;
    towerStats[0][1][1].fireRate = 30;
    towerStats[0][1][1].homing = false;
    towerStats[0][1][1].range = 100;
    towerStats[0][1][1].speed = 4;
    towerStats[0][1][1].type = 1;

    //1.1 lvl 2
    towerStats[0][1][2].cost = 100;
    towerStats[0][1][2].damage = 10;
    towerStats[0][1][2].fireRate = 30;
    towerStats[0][1][2].homing = false;
    towerStats[0][1][2].range = 100;
    towerStats[0][1][2].speed = 4;
    towerStats[0][1][2].type = 1;

    //1.1 lvl 3
    towerStats[0][1][3].cost = 100;
    towerStats[0][1][3].damage = 10;
    towerStats[0][1][3].fireRate = 30;
    towerStats[0][1][3].homing = false;
    towerStats[0][1][3].range = 100;
    towerStats[0][1][3].speed = 4;
    towerStats[0][1][3].type = 1;

    //1.2 lvl 0
    towerStats[0][2][0].cost = 100;
    towerStats[0][2][0].damage = 10;
    towerStats[0][2][0].fireRate = 30;
    towerStats[0][2][0].homing = false;
    towerStats[0][2][0].range = 100;
    towerStats[0][2][0].speed = 4;
    towerStats[0][2][0].type = 2;

    //1.2 lvl 1
    towerStats[0][2][1].cost = 100;
    towerStats[0][2][1].damage = 10;
    towerStats[0][2][1].fireRate = 30;
    towerStats[0][2][1].homing = false;
    towerStats[0][2][1].range = 100;
    towerStats[0][2][1].speed = 4;
    towerStats[0][2][1].type = 2;

    //1.2 lvl 2
    towerStats[0][2][2].cost = 100;
    towerStats[0][2][2].damage = 10;
    towerStats[0][2][2].fireRate = 30;
    towerStats[0][2][2].homing = false;
    towerStats[0][2][2].range = 100;
    towerStats[0][2][2].speed = 4;
    towerStats[0][2][2].type = 2;

    //1.2 lvl 3
    towerStats[0][2][3].cost = 100;
    towerStats[0][2][3].damage = 10;
    towerStats[0][2][3].fireRate = 30;
    towerStats[0][2][3].homing = false;
    towerStats[0][2][3].range = 100;
    towerStats[0][2][3].speed = 4;
    towerStats[0][2][3].type = 2;

    //1.3 lvl 0
    towerStats[0][3][0].cost = 100;
    towerStats[0][3][0].damage = 10;
    towerStats[0][3][0].fireRate = 30;
    towerStats[0][3][0].homing = false;
    towerStats[0][3][0].range = 100;
    towerStats[0][3][0].speed = 4;
    towerStats[0][3][0].type = 3;

    //1.3 lvl 1
    towerStats[0][3][1].cost = 100;
    towerStats[0][3][1].damage = 10;
    towerStats[0][3][1].fireRate = 30;
    towerStats[0][3][1].homing = false;
    towerStats[0][3][1].range = 100;
    towerStats[0][3][1].speed = 4;
    towerStats[0][3][1].type = 3;

    //1.3 lvl 2
    towerStats[0][3][2].cost = 100;
    towerStats[0][3][2].damage = 10;
    towerStats[0][3][2].fireRate = 30;
    towerStats[0][3][2].homing = false;
    towerStats[0][3][2].range = 100;
    towerStats[0][3][2].speed = 4;
    towerStats[0][3][2].type = 3;

    //1.3 lvl 3
    towerStats[0][3][3].cost = 100;
    towerStats[0][3][3].damage = 10;
    towerStats[0][3][3].fireRate = 30;
    towerStats[0][3][3].homing = false;
    towerStats[0][3][3].range = 100;
    towerStats[0][3][3].speed = 4;
    towerStats[0][3][3].type = 3;

    //basic 2
    towerStats[1][0][0].cost = 100;
    towerStats[1][0][0].damage = 10;
    towerStats[1][0][0].fireRate = 30;
    towerStats[1][0][0].homing = true;
    towerStats[1][0][0].range = 200;
    towerStats[1][0][0].speed = 1;
    towerStats[1][0][0].type = 4;

    //2.1 lvl 0
    towerStats[1][1][0].cost = 100;
    towerStats[1][1][0].damage = 20;
    towerStats[1][1][0].fireRate = 60;
    towerStats[1][1][0].homing = false;
    towerStats[1][1][0].range = 200;
    towerStats[1][1][0].speed = 10;
    towerStats[1][1][0].type = 5;

    //2.1 lvl 1
    towerStats[1][1][1].cost = 100;
    towerStats[1][1][1].damage = 30;
    towerStats[1][1][1].fireRate = 50;
    towerStats[1][1][1].homing = false;
    towerStats[1][1][1].range = 300;
    towerStats[1][1][1].speed = 10;
    towerStats[1][1][1].type = 5;

    //2.1 lvl 2
    towerStats[1][1][2].cost = 100;
    towerStats[1][1][2].damage = 40;
    towerStats[1][1][2].fireRate = 40;
    towerStats[1][1][2].homing = false;
    towerStats[1][1][2].range = 400;
    towerStats[1][1][2].speed = 10;
    towerStats[1][1][2].type = 5;

    //2.1 lvl 3
    towerStats[1][1][3].cost = 100;
    towerStats[1][1][3].damage = 50;
    towerStats[1][1][3].fireRate = 30;
    towerStats[1][1][3].homing = false;
    towerStats[1][1][3].range = 500;
    towerStats[1][1][3].speed = 10;
    towerStats[1][1][3].type = 5;

    //2.2 lvl 0
    towerStats[1][2][0].cost = 100;
    towerStats[1][2][0].damage = 10;
    towerStats[1][2][0].fireRate = 60;
    towerStats[1][2][0].homing = true;
    towerStats[1][2][0].range = 200;
    towerStats[1][2][0].speed = 0.5;
    towerStats[1][2][0].type = 6;

    //2.2 lvl 1
    towerStats[1][2][1].cost = 100;
    towerStats[1][2][1].damage = 20;
    towerStats[1][2][1].fireRate = 60;
    towerStats[1][2][1].homing = true;
    towerStats[1][2][1].range = 200;
    towerStats[1][2][1].speed = 0.5;
    towerStats[1][2][1].type = 6;

    //2.2 lvl 2
    towerStats[1][2][2].cost = 100;
    towerStats[1][2][2].damage = 30;
    towerStats[1][2][2].fireRate = 60;
    towerStats[1][2][2].homing = true;
    towerStats[1][2][2].range = 200;
    towerStats[1][2][2].speed = 0.5;
    towerStats[1][2][2].type = 6;

    //2.2 lvl 3
    towerStats[1][2][3].cost = 100;
    towerStats[1][2][3].damage = 40;
    towerStats[1][2][3].fireRate = 60;
    towerStats[1][2][3].homing = true;
    towerStats[1][2][3].range = 200;
    towerStats[1][2][3].speed = 0.5;
    towerStats[1][2][3].type = 6;

    //2.3 lvl 0
    towerStats[1][3][0].cost = 100;
    towerStats[1][3][0].damage = 10;
    towerStats[1][3][0].fireRate = 30;
    towerStats[1][3][0].homing = true;
    towerStats[1][3][0].range = 100;
    towerStats[1][3][0].speed = 4;
    towerStats[1][3][0].type = 7;

    //2.3 lvl 1
    towerStats[1][3][1].cost = 100;
    towerStats[1][3][1].damage = 10;
    towerStats[1][3][1].fireRate = 30;
    towerStats[1][3][1].homing = true;
    towerStats[1][3][1].range = 100;
    towerStats[1][3][1].speed = 4;
    towerStats[1][3][1].type = 7;

    //2.3 lvl 2
    towerStats[1][3][2].cost = 100;
    towerStats[1][3][2].damage = 10;
    towerStats[1][3][2].fireRate = 30;
    towerStats[1][3][2].homing = true;
    towerStats[1][3][2].range = 100;
    towerStats[1][3][2].speed = 4;
    towerStats[1][3][2].type = 7;

    //2.3 lvl 3
    towerStats[1][3][3].cost = 100;
    towerStats[1][3][3].damage = 10;
    towerStats[1][3][3].fireRate = 30;
    towerStats[1][3][3].homing = true;
    towerStats[1][3][3].range = 100;
    towerStats[1][3][3].speed = 4;
    towerStats[1][3][3].type = 7;

    //basic 3
    towerStats[2][0][0].cost = 100;
    towerStats[2][0][0].damage = 10;
    towerStats[2][0][0].fireRate = 30;
    towerStats[2][0][0].homing = false;
    towerStats[2][0][0].range = 60;
    towerStats[2][0][0].speed = 4;
    towerStats[2][0][0].type = 8;

    //3.1 lvl 0
    towerStats[2][1][0].cost = 100;
    towerStats[2][1][0].damage = 10;
    towerStats[2][1][0].fireRate = 30;
    towerStats[2][1][0].homing = false;
    towerStats[2][1][0].range = 60;
    towerStats[2][1][0].speed = 4;
    towerStats[2][1][0].type = 9;

    //3.1 lvl 1
    towerStats[2][1][1].cost = 100;
    towerStats[2][1][1].damage = 10;
    towerStats[2][1][1].fireRate = 30;
    towerStats[2][1][1].homing = false;
    towerStats[2][1][1].range = 60;
    towerStats[2][1][1].speed = 4;
    towerStats[2][1][1].type = 9;

    //3.1 lvl 2
    towerStats[2][1][2].cost = 100;
    towerStats[2][1][2].damage = 10;
    towerStats[2][1][2].fireRate = 30;
    towerStats[2][1][2].homing = false;
    towerStats[2][1][2].range = 60;
    towerStats[2][1][2].speed = 4;
    towerStats[2][1][2].type = 9;

    //3.1 lvl 3
    towerStats[2][1][3].cost = 100;
    towerStats[2][1][3].damage = 10;
    towerStats[2][1][3].fireRate = 30;
    towerStats[2][1][3].homing = false;
    towerStats[2][1][3].range = 60;
    towerStats[2][1][3].speed = 4;
    towerStats[2][1][3].type = 9;

    //3.2 lvl 0
    towerStats[2][2][0].cost = 100;
    towerStats[2][2][0].damage = 10;
    towerStats[2][2][0].fireRate = 30;
    towerStats[2][2][0].homing = false;
    towerStats[2][2][0].range = 60;
    towerStats[2][2][0].speed = 4;
    towerStats[2][2][0].type = 10;

    //3.2 lvl 1
    towerStats[2][2][1].cost = 100;
    towerStats[2][2][1].damage = 10;
    towerStats[2][2][1].fireRate = 30;
    towerStats[2][2][1].homing = false;
    towerStats[2][2][1].range = 60;
    towerStats[2][2][1].speed = 4;
    towerStats[2][2][1].type = 10;

    //3.2 lvl 2
    towerStats[2][2][2].cost = 100;
    towerStats[2][2][2].damage = 10;
    towerStats[2][2][2].fireRate = 30;
    towerStats[2][2][2].homing = false;
    towerStats[2][2][2].range = 60;
    towerStats[2][2][2].speed = 4;
    towerStats[2][2][2].type = 10;

    //3.2 lvl 3
    towerStats[2][2][3].cost = 100;
    towerStats[2][2][3].damage = 10;
    towerStats[2][2][3].fireRate = 30;
    towerStats[2][2][3].homing = false;
    towerStats[2][2][3].range = 60;
    towerStats[2][2][3].speed = 4;
    towerStats[2][2][3].type = 10;

    //3.3 lvl 0
    towerStats[2][3][0].cost = 100;
    towerStats[2][3][0].damage = 10;
    towerStats[2][3][0].fireRate = 30;
    towerStats[2][3][0].homing = false;
    towerStats[2][3][0].range = 60;
    towerStats[2][3][0].speed = 4;
    towerStats[2][3][0].type = 11;

    //3.3 lvl 1
    towerStats[2][3][1].cost = 100;
    towerStats[2][3][1].damage = 10;
    towerStats[2][3][1].fireRate = 30;
    towerStats[2][3][1].homing = false;
    towerStats[2][3][1].range = 60;
    towerStats[2][3][1].speed = 4;
    towerStats[2][3][1].type = 11;

    //3.3 lvl 2
    towerStats[2][3][2].cost = 100;
    towerStats[2][3][2].damage = 10;
    towerStats[2][3][2].fireRate = 30;
    towerStats[2][3][2].homing = false;
    towerStats[2][3][2].range = 60;
    towerStats[2][3][2].speed = 4;
    towerStats[2][3][2].type = 11;

    //3.3 lvl 3
    towerStats[2][3][3].cost = 100;
    towerStats[2][3][3].damage = 10;
    towerStats[2][3][3].fireRate = 30;
    towerStats[2][3][3].homing = false;
    towerStats[2][3][3].range = 60;
    towerStats[2][3][3].speed = 4;
    towerStats[2][3][3].type = 11;
}

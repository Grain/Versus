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
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void initializeStats()
{
    descriptions[0] = "Basic tower 0\n\nA crappy tower\n\n";
    descriptions[1] = "Basic tower 1\n\nA rapid fire tower\n\n";
    descriptions[2] = "Basic tower 2\n\nA crappy tower\n\n";
    descriptions[3] = "Basic tower 3\n\nA tower that places random\nbuffs on your creeps\n\n";
    descriptions[4] = "Basic tower 4\n\nA crappy tower..that\nshoots missiles!\n\n";
    descriptions[5] = "Basic tower 5\n\nA snipa tower\n\n";
    descriptions[6] = "Basic tower 6\n\nA missile tower that does\ndamage in an area\n\n";
    descriptions[7] = "Basic tower 7\n\nA missile tower that\nheals your creeps in an area\n\n";
    descriptions[8] = "Basic tower 8\n\nA crappy splash tower\n\n";
    descriptions[9] = "Basic tower 9\n\nA crappy splash slow tower\n\n";
    descriptions[10] = "Basic tower 10\n\nA crappy splash damage\namplification tower\n\n";
    descriptions[11] = "Basic tower 11\n\nA crappy splash tower\n\n";

    //basic 1
    towerStats[0][0][0].cost = 100;
    towerStats[0][0][0].damage = 20;
    towerStats[0][0][0].fireRate = 30;
    towerStats[0][0][0].homing = false;
    towerStats[0][0][0].range = 102;
    towerStats[0][0][0].speed = 4;
    towerStats[0][0][0].type = 0;

    //1.1 lvl 0
    towerStats[0][1][0].cost = 100;
    towerStats[0][1][0].damage = 35;
    towerStats[0][1][0].fireRate = 30;
    towerStats[0][1][0].homing = false;
    towerStats[0][1][0].range = 102;
    towerStats[0][1][0].speed = 4;
    towerStats[0][1][0].type = 1;

    //1.1 lvl 1
    towerStats[0][1][1].cost = 100;
    towerStats[0][1][1].damage = 50;
    towerStats[0][1][1].fireRate = 30;
    towerStats[0][1][1].homing = false;
    towerStats[0][1][1].range = 102;
    towerStats[0][1][1].speed = 4;
    towerStats[0][1][1].type = 1;

    //1.1 lvl 2
    towerStats[0][1][2].cost = 100;
    towerStats[0][1][2].damage = 65;
    towerStats[0][1][2].fireRate = 30;
    towerStats[0][1][2].homing = false;
    towerStats[0][1][2].range = 102;
    towerStats[0][1][2].speed = 4;
    towerStats[0][1][2].type = 1;

    //1.1 lvl 3
    towerStats[0][1][3].cost = 100;
    towerStats[0][1][3].damage = 80;
    towerStats[0][1][3].fireRate = 30;
    towerStats[0][1][3].homing = false;
    towerStats[0][1][3].range = 102;
    towerStats[0][1][3].speed = 4;
    towerStats[0][1][3].type = 1;

    //1.2 lvl 0
    towerStats[0][2][0].cost = 100;
    towerStats[0][2][0].damage = 1;
    towerStats[0][2][0].fireRate = 2;
    towerStats[0][2][0].homing = false;
    towerStats[0][2][0].range = 102;
    towerStats[0][2][0].speed = 3;
    towerStats[0][2][0].type = 2;

    //1.2 lvl 1
    towerStats[0][2][1].cost = 100;
    towerStats[0][2][1].damage = 2;
    towerStats[0][2][1].fireRate = 2;
    towerStats[0][2][1].homing = false;
    towerStats[0][2][1].range = 102;
    towerStats[0][2][1].speed = 3;
    towerStats[0][2][1].type = 2;

    //1.2 lvl 2
    towerStats[0][2][2].cost = 100;
    towerStats[0][2][2].damage = 3;
    towerStats[0][2][2].fireRate = 2;
    towerStats[0][2][2].homing = false;
    towerStats[0][2][2].range = 102;
    towerStats[0][2][2].speed = 3;
    towerStats[0][2][2].type = 2;

    //1.2 lvl 3
    towerStats[0][2][3].cost = 100;
    towerStats[0][2][3].damage = 4;
    towerStats[0][2][3].fireRate = 2;
    towerStats[0][2][3].homing = false;
    towerStats[0][2][3].range = 102;
    towerStats[0][2][3].speed = 3;
    towerStats[0][2][3].type = 2;

    //1.3 lvl 0
    towerStats[0][3][0].cost = 500;
    towerStats[0][3][0].damage = 10;
    towerStats[0][3][0].fireRate = 30;
    towerStats[0][3][0].homing = false;
    towerStats[0][3][0].range = 102;
    towerStats[0][3][0].speed = 4;
    towerStats[0][3][0].type = 3;

    //1.3 lvl 1
    towerStats[0][3][1].cost = 750;
    towerStats[0][3][1].damage = 20;
    towerStats[0][3][1].fireRate = 30;
    towerStats[0][3][1].homing = false;
    towerStats[0][3][1].range = 102;
    towerStats[0][3][1].speed = 4;
    towerStats[0][3][1].type = 3;

    //1.3 lvl 2
    towerStats[0][3][2].cost = 1000;
    towerStats[0][3][2].damage = 30;
    towerStats[0][3][2].fireRate = 30;
    towerStats[0][3][2].homing = false;
    towerStats[0][3][2].range = 102;
    towerStats[0][3][2].speed = 4;
    towerStats[0][3][2].type = 3;

    //1.3 lvl 3
    towerStats[0][3][3].cost = 1500;
    towerStats[0][3][3].damage = 40;
    towerStats[0][3][3].fireRate = 30;
    towerStats[0][3][3].homing = false;
    towerStats[0][3][3].range = 102;
    towerStats[0][3][3].speed = 4;
    towerStats[0][3][3].type = 3;

    //basic 2
    towerStats[1][0][0].cost = 100;
    towerStats[1][0][0].damage = 10;
    towerStats[1][0][0].fireRate = 20;
    towerStats[1][0][0].homing = true;
    towerStats[1][0][0].range = 123;
    towerStats[1][0][0].speed = 1.5;
    towerStats[1][0][0].type = 4;

    //2.1 lvl 0
    towerStats[1][1][0].cost = 100;
    towerStats[1][1][0].damage = 50;
    towerStats[1][1][0].fireRate = 120;
    towerStats[1][1][0].homing = true;
    towerStats[1][1][0].range = 143;
    towerStats[1][1][0].speed = 10;
    towerStats[1][1][0].type = 5;

    //2.1 lvl 1
    towerStats[1][1][1].cost = 100;
    towerStats[1][1][1].damage = 100;
    towerStats[1][1][1].fireRate = 120;
    towerStats[1][1][1].homing = true;
    towerStats[1][1][1].range = 164;
    towerStats[1][1][1].speed = 10;
    towerStats[1][1][1].type = 5;

    //2.1 lvl 2
    towerStats[1][1][2].cost = 100;
    towerStats[1][1][2].damage = 150;
    towerStats[1][1][2].fireRate = 120;
    towerStats[1][1][2].homing = true;
    towerStats[1][1][2].range = 184;
    towerStats[1][1][2].speed = 10;
    towerStats[1][1][2].type = 5;

    //2.1 lvl 3
    towerStats[1][1][3].cost = 100;
    towerStats[1][1][3].damage = 200;
    towerStats[1][1][3].fireRate = 120;
    towerStats[1][1][3].homing = true;
    towerStats[1][1][3].range = 205;
    towerStats[1][1][3].speed = 10;
    towerStats[1][1][3].type = 5;

    //2.2 lvl 0
    towerStats[1][2][0].cost = 100;
    towerStats[1][2][0].damage = 60;
    towerStats[1][2][0].fireRate = 60;
    towerStats[1][2][0].homing = true;
    towerStats[1][2][0].range = 123;
    towerStats[1][2][0].speed = 0.75;
    towerStats[1][2][0].type = 6;

    //2.2 lvl 1
    towerStats[1][2][1].cost = 100;
    towerStats[1][2][1].damage = 70;
    towerStats[1][2][1].fireRate = 60;
    towerStats[1][2][1].homing = true;
    towerStats[1][2][1].range = 143;
    towerStats[1][2][1].speed = 0.75;
    towerStats[1][2][1].type = 6;

    //2.2 lvl 2
    towerStats[1][2][2].cost = 100;
    towerStats[1][2][2].damage = 80;
    towerStats[1][2][2].fireRate = 60;
    towerStats[1][2][2].homing = true;
    towerStats[1][2][2].range = 143;
    towerStats[1][2][2].speed = 0.75;
    towerStats[1][2][2].type = 6;

    //2.2 lvl 3
    towerStats[1][2][3].cost = 200;
    towerStats[1][2][3].damage = 100;
    towerStats[1][2][3].fireRate = 60;
    towerStats[1][2][3].homing = true;
    towerStats[1][2][3].range = 143;
    towerStats[1][2][3].speed = 0.75;
    towerStats[1][2][3].type = 6;

    //2.3 lvl 0
    towerStats[1][3][0].cost = 100;
    towerStats[1][3][0].damage = 30;
    towerStats[1][3][0].fireRate = 30;
    towerStats[1][3][0].homing = true;
    towerStats[1][3][0].range = 184;
    towerStats[1][3][0].speed = 1.5;
    towerStats[1][3][0].type = 7;

    //2.3 lvl 1
    towerStats[1][3][1].cost = 100;
    towerStats[1][3][1].damage = 40;
    towerStats[1][3][1].fireRate = 40;
    towerStats[1][3][1].homing = true;
    towerStats[1][3][1].range = 184;
    towerStats[1][3][1].speed = 1.5;
    towerStats[1][3][1].type = 7;

    //2.3 lvl 2
    towerStats[1][3][2].cost = 100;
    towerStats[1][3][2].damage = 50;
    towerStats[1][3][2].fireRate = 40;
    towerStats[1][3][2].homing = true;
    towerStats[1][3][2].range = 184;
    towerStats[1][3][2].speed = 1.5;
    towerStats[1][3][2].type = 7;

    //2.3 lvl 3
    towerStats[1][3][3].cost = 100;
    towerStats[1][3][3].damage = 60;
    towerStats[1][3][3].fireRate = 40;
    towerStats[1][3][3].homing = true;
    towerStats[1][3][3].range = 184;
    towerStats[1][3][3].speed = 1.5;
    towerStats[1][3][3].type = 7;

    //basic 3
    towerStats[2][0][0].cost = 100;
    towerStats[2][0][0].damage = 20;
    towerStats[2][0][0].fireRate = 30;
    towerStats[2][0][0].homing = false;
    towerStats[2][0][0].range = 61;
    towerStats[2][0][0].speed = 4;
    towerStats[2][0][0].type = 8;

    //3.1 lvl 0
    towerStats[2][1][0].cost = 100;
    towerStats[2][1][0].damage = 10;
    towerStats[2][1][0].fireRate = 30;
    towerStats[2][1][0].homing = false;
    towerStats[2][1][0].range = 61;
    towerStats[2][1][0].speed = 4;
    towerStats[2][1][0].type = 9;

    //3.1 lvl 1
    towerStats[2][1][1].cost = 150;
    towerStats[2][1][1].damage = 20;
    towerStats[2][1][1].fireRate = 30;
    towerStats[2][1][1].homing = false;
    towerStats[2][1][1].range = 61;
    towerStats[2][1][1].speed = 4;
    towerStats[2][1][1].type = 9;

    //3.1 lvl 2
    towerStats[2][1][2].cost = 200;
    towerStats[2][1][2].damage = 30;
    towerStats[2][1][2].fireRate = 30;
    towerStats[2][1][2].homing = false;
    towerStats[2][1][2].range = 61;
    towerStats[2][1][2].speed = 4;
    towerStats[2][1][2].type = 9;

    //3.1 lvl 3
    towerStats[2][1][3].cost = 250;
    towerStats[2][1][3].damage = 40;
    towerStats[2][1][3].fireRate = 30;
    towerStats[2][1][3].homing = false;
    towerStats[2][1][3].range = 61;
    towerStats[2][1][3].speed = 4;
    towerStats[2][1][3].type = 9;

    //3.2 lvl 0
    towerStats[2][2][0].cost = 100;
    towerStats[2][2][0].damage = 10;
    towerStats[2][2][0].fireRate = 30;
    towerStats[2][2][0].homing = false;
    towerStats[2][2][0].range = 61;
    towerStats[2][2][0].speed = 4;
    towerStats[2][2][0].type = 10;

    //3.2 lvl 1
    towerStats[2][2][1].cost = 120;
    towerStats[2][2][1].damage = 20;
    towerStats[2][2][1].fireRate = 30;
    towerStats[2][2][1].homing = false;
    towerStats[2][2][1].range = 61;
    towerStats[2][2][1].speed = 4;
    towerStats[2][2][1].type = 10;

    //3.2 lvl 2
    towerStats[2][2][2].cost = 200;
    towerStats[2][2][2].damage = 30;
    towerStats[2][2][2].fireRate = 30;
    towerStats[2][2][2].homing = false;
    towerStats[2][2][2].range = 61;
    towerStats[2][2][2].speed = 4;
    towerStats[2][2][2].type = 10;

    //3.2 lvl 3
    towerStats[2][2][3].cost = 250;
    towerStats[2][2][3].damage = 40;
    towerStats[2][2][3].fireRate = 30;
    towerStats[2][2][3].homing = false;
    towerStats[2][2][3].range = 61;
    towerStats[2][2][3].speed = 4;
    towerStats[2][2][3].type = 10;

    //3.3 lvl 0
    towerStats[2][3][0].cost = 100;
    towerStats[2][3][0].damage = 30;
    towerStats[2][3][0].fireRate = 30;
    towerStats[2][3][0].homing = false;
    towerStats[2][3][0].range = 61;
    towerStats[2][3][0].speed = 4;
    towerStats[2][3][0].type = 11;

    //3.3 lvl 1
    towerStats[2][3][1].cost = 100;
    towerStats[2][3][1].damage = 30;
    towerStats[2][3][1].fireRate = 20;
    towerStats[2][3][1].homing = false;
    towerStats[2][3][1].range = 61;
    towerStats[2][3][1].speed = 4;
    towerStats[2][3][1].type = 11;

    //3.3 lvl 2
    towerStats[2][3][2].cost = 150;
    towerStats[2][3][2].damage = 40;
    towerStats[2][3][2].fireRate = 20;
    towerStats[2][3][2].homing = false;
    towerStats[2][3][2].range = 61;
    towerStats[2][3][2].speed = 4;
    towerStats[2][3][2].type = 11;

    //3.3 lvl 3
    towerStats[2][3][3].cost = 150;
    towerStats[2][3][3].damage = 40;
    towerStats[2][3][3].fireRate = 15;
    towerStats[2][3][3].homing = false;
    towerStats[2][3][3].range = 61;
    towerStats[2][3][3].speed = 4;
    towerStats[2][3][3].type = 11;
}

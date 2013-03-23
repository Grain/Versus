#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <cstdio>
#include <SFML/Graphics.hpp>

struct Keys
{
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key select;
    sf::Keyboard::Key back;
};

struct Settings
{
    Keys leftPlayer, rightPlayer;
    int effectVolume, musicVolume;
    bool enableMouse;

    bool doubleBuffered;
};

sf::Vector2i gridPosition(sf::Vector2i);

extern Settings settings;

const int XRES = 1024;
const int YRES = 576;

//grid consts
const int BOXDIMENSIONS = 40;   //each box in the grid is 40x40, not including the lines
const int GRIDX = 10;
const int GRIDY = 9;  //grid is 10x9 on each side
const int MIDDLE = 3;  //3 box wide in the middle

#endif // GLOBAL_H_INCLUDED

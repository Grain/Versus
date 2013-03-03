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
    bool enableMouseTwoPlayer;
};

sf::Vector2i gridPosition(sf::Vector2i);

const int xRes = 1024;
const int yRes = 576;

#endif // GLOBAL_H_INCLUDED

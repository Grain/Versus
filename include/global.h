#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "gameaudio.h"

//forward declaration
class GameAudio;

struct Keys
{
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key select;
    sf::Keyboard::Key back;
    sf::Keyboard::Key speed;
    sf::Keyboard::Key hotkey1;
    sf::Keyboard::Key hotkey2;
    sf::Keyboard::Key hotkey3;
    sf::Keyboard::Key hotkey4;
};

struct Settings
{
    Keys leftPlayer, rightPlayer;
    int effectVolume, musicVolume;
    bool enableMouse;

    bool doubleBuffered;    //sfml actually has double buffering by default, this turns on drawing to a secondary buffer before drawing on screen
    int fastForwardSpeed;
    bool selectAfterUpgrade;    //whether to keep upgrades focused after buying an upgrade
};

struct Stats    //tower/projectile stats
{
    int cost;
    int fireRate;       //frames/shot       eg. if FPS = 30, fireRate = 30 would result in 1 shot/sec
    int range;
    int damage;
    int type;       //projectile type
    bool homing;
    double speed;
};

struct CreepStats
{
    int cooldown;
    int timeLeft;
    int amount;
    int type;
    double speed;
    int hp;
};

sf::Vector2i gridPosition(sf::Vector2i);
sf::Vector2i coordinatePosition(sf::Vector2i);
double distance(sf::Vector2f, sf::Vector2f);
void initializeStats();

extern Settings settings;
extern GameAudio gameAudio;
extern Stats towerStats[3][4][4];
extern std::string descriptions[12];

const int XRES = 1024;
const int YRES = 576;

const int FPS = 30;

//grid consts
const int BOXDIMENSIONS = 40;   //each box in the grid is 40x40, not including the lines
const int GRIDX = 10;
const int GRIDY = 9;  //grid is 10x9 on each side
const int MIDDLE = 3;  //3 box wide in the middle

#endif // GLOBAL_H_INCLUDED

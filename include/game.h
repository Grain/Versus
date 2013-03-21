#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "tower.h"
#include "interface.h"
#include <vector>
#include <queue>

class Game
{
    public:
        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        //setters

        //functions
        int update(sf::Vector2i);
        void draw(sf::RenderWindow*);
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;

        //functions
        void initializeGrid(sf::RenderTarget*, sf::Color, sf::Color);
        void newTower(sf::Vector2i);
        void calculateDistances();

        //Sprites and RenderTextures
        sf::Sprite gridSprite;          //grid
        sf::RenderTexture gridTexture;

        sf::Sprite towerSprite;         //tower
        sf::RenderTexture towerTexture;

        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        Interface interface;

        std::vector<Tower*> towers;
        bool map[GRIDX * 2 + MIDDLE][GRIDY];

        int distancesLeft[GRIDX * 2 + MIDDLE][GRIDY];   //left = going to left side, right = going to right side
        int distancesRight[GRIDX * 2 + MIDDLE][GRIDY];

        int pathsLeft[GRIDX * 2 + MIDDLE][GRIDY];   //not int
        int pathsRight[GRIDX * 2 + MIDDLE][GRIDY];   //not int
};

#endif // GAME_H

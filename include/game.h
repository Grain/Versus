#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "tower.h"
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
        void newGame();
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;

        enum Players{left, right, both};

        struct KeyState
        {
            bool left;
            bool right;
            bool up;
            bool down;
            bool select;
            bool back;
        };

        //functions
        void initializeGrid(sf::RenderTarget*, sf::Color, sf::Color);
        void newTower(sf::Vector2i);
        void calculateDistances();

        //vars
        Players players;
        sf::Vector2i prevMouse;
        KeyState prevKeys[2];
        sf::Texture selectorTextures[2];
        sf::RectangleShape selector[2];
        sf::Vector2i selectorCoordinates[2];

        sf::RenderTexture canvas;
        sf::Sprite drawable;

        std::vector<Tower*> towers;
        bool map[GRIDX * 2 + MIDDLE][GRIDY];

        int distancesLeft[GRIDX * 2 + MIDDLE][GRIDY];   //left = going to left side, right = going to right side
        int distancesRight[GRIDX * 2 + MIDDLE][GRIDY];
};

#endif // GAME_H

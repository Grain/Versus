#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "tower.h"
#include <vector>

class Game
{
    public:
        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        //setters

        //functions
        void update(sf::Vector2i);
        void draw(sf::RenderWindow*);
    protected:
    private:
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

        //Sprites and RenderTextures
        sf::Sprite gridSprite;          //grid
        sf::RenderTexture gridTexture;

        sf::Sprite towerSprite;         //tower
        sf::RenderTexture towerTexture;

        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        KeyState prevLeft, prevRight;
        std::vector<Tower*> towers;
        bool map[GRIDX * 2 + MIDDLE][GRIDY];
};

#endif // GAME_H

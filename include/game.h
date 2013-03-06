#ifndef GAME_H
#define GAME_H

#include "drawable.h"
#include "global.h"
#include "tower.h"
#include <vector>

class Game : public Drawable
{
    public:
        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        //setters

        //functions
        void update(sf::Vector2i);
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
        void initializeGrid(sf::Color, sf::Color);
        void newTower(sf::Vector2i);

        //Sprites and RenderTextures
        sf::Sprite gridSprite;          //grid
        sf::RenderTexture gridTexture;

        sf::Sprite towerSprite;         //tower
        sf::RenderTexture towerTexture;

        //vars
        KeyState prevLeft, prevRight;
        std::vector<Tower*> towers;
        bool map[GRIDX * 2 + MIDDLE][GRIDY];
};

#endif // GAME_H

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "global.h"

class Game
{
    public:
        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        sf::Sprite getSprite();
        //setters

        //functions
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
        sf::Sprite initializeGrid(sf::Color left, sf::Color right);
        void update();

        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;
        KeyState prevLeft, prevRight;
};

#endif // GAME_H

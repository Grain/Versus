#ifndef GAME_H
#define GAME_H

#include "Drawable.h"
#include "global.h"
#include "tower.h"

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
        sf::Sprite initializeGrid(sf::Color, sf::Color);

        //vars
        sf::Sprite field;
        KeyState prevLeft, prevRight;
        Tower tower;
};

#endif // GAME_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include "global.h"
#include "button.h"

class Interface
{
    public:
        //enum
        enum Players{left, right, both};
        //ctor/dtor
        Interface();
        virtual ~Interface();
        //getters
        Players getPlayers();
        //setters
        void setPlayers(Players);
        //functions
        void draw(sf::RenderTarget*);
        int update(sf::Vector2i);

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

        //vars
        sf::Vector2i prevMouse;
        Players players;

        //selectors
        sf::Texture selector, reflectedSelector;
        //left
        KeyState prevLeft;
        sf::RectangleShape leftSelector;
        sf::Vector2i leftCoordinates;
        //right
        KeyState prevRight;
        sf::RectangleShape rightSelector;
        sf::Vector2i rightCoordinates;
};

#endif // INTERFACE_H
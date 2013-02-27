#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "global.h"

class Menu
{
    public:
        //ctor/dtor
        Menu();
        virtual ~Menu();
        //getters
        sf::Sprite getSprite();
        //setters

        //functions
        void update(sf::Vector2i);
    protected:
    private:
        //functions

        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;
};

#endif // MENU_H

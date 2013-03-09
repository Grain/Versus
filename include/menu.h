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

        //setters

        //functions
        void draw(sf::RenderWindow*);
        void update(sf::Vector2i);
    protected:
    private:
        //functions
        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::RectangleShape background;
        sf::Texture backgroundTexture;
};

#endif // MENU_H

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "global.h"
#include "button.h"
#include <vector>

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
        int update(sf::Vector2i);
    protected:
    private:
        //functions
        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::RectangleShape background;
        sf::Texture backgroundTexture;

        std::vector <Button*> mainMenu;
};

#endif // MENU_H

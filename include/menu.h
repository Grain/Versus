#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include "global.h"

class Menu : public Drawable
{
    public:
        //ctor/dtor
        Menu();
        virtual ~Menu();
        //getters
        //setters

        //functions
        void update(sf::Vector2i);
    protected:
    private:
        //functions
        sf::Sprite initializeBtns();
        sf::Sprite initializeMenu();
        //vars
        sf::Sprite mainMenu;
        sf::Sprite mainBtns;
};

#endif // MENU_H

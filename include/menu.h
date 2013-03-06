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
        int getState();
        //setters
        void setState(int);
        //functions
        int checkClick(sf::Vector2i); // may rename this
        void update(sf::Vector2i);
    protected:
        int menuState;
    private:
        //functions
        void initializeMenu();
        void redrawMenu();
        //vars
        bool startBtnMO;
        sf::Sprite menuSprite;
        sf::RectangleShape background, startBtn, optionsBtn, exitBtn;
        sf::RenderTexture menuTexture;
        sf::Texture backgroundTexture, startBtnTexture, startBtnMOTexture, optionsBtnTexture, exitBtnTexture;
};

#endif // MENU_H

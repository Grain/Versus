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
        sf::RectangleShape getBackground();
        sf::RectangleShape getStartBtn();
        sf::RectangleShape getOptionsBtn();
        sf::RectangleShape getExitBtn();
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
        bool startBtnMO, optionsBtnMO, exitBtnMO;
        sf::Sprite menuSprite;
        sf::RectangleShape background, startBtn, optionsBtn, exitBtn;
        sf::RenderTexture menuTexture;
        sf::Texture backgroundTexture, startBtnTexture, startBtnMOTexture, optionsBtnTexture, optionsBtnMOTexture, exitBtnTexture, exitBtnMOTexture;
};

#endif // MENU_H

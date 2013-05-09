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
        static const char * const keyNames[];
        static const char * const hotkeyNames[];
        //functions
        void readSettings();
        void writeSettings();
        void updateSettings();
        void bindKey();
        bool checkDuplicates();
        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::RectangleShape background;
        sf::Texture mainBackgroundTexture;
        sf::Texture settingsBackgroundTexture;
        sf::RectangleShape bindBackground;
        sf::Text bindText;
        char bindMessage[256];

        std::vector <Button*> mainMenu;
        std::vector <Button*> settingsMenu;
        std::vector <sf::Text*> settingsText;

        int currentKey;
        bool isBinding;
};

#endif // MENU_H

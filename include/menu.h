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
        void updateScore();
        void updateTips();
    protected:
    private:
        static const char * const keyNames[];
        static const char * const hotkeyNames[];
        static const char * const tipList[];

        static const int NUMBEROFTIPS = 2;
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

        sf::Text highScore;

        std::vector <Button*> mainMenu;
        std::vector <Button*> settingsMenu;
        std::vector <Button*> singleMenu;
        std::vector <sf::Text*> settingsText;

        int currentKey;
        bool isBinding;

        sf::Text tips;
        sf::RectangleShape tipsBackground;
};

#endif // MENU_H

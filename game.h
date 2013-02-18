#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>


class Game
{
    public:
        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        sf::Sprite getSprite();
        //setters

        //functions
    protected:
    private:
        //functions
        sf::Sprite initializeGrid(sf::Color left, sf::Color right);

        //vars
        sf::RenderTexture canvas;
        sf::Sprite drawable;
};

#endif // GAME_H

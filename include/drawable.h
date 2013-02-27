#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable
{
    public:
        //ctor/dtor
        Drawable();
        virtual ~Drawable();
        //getters
        sf::Sprite getSprite();
        //setters

        //functions
    protected:
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::Vector2i size;
        sf::Vector2f position;  //maybe both vector2f?
    private:
};

#endif // DRAWABLE_H

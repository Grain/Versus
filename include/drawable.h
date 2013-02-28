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
        sf::Vector2i getSize();     //size getters/setters needed or no?
        sf::Vector2f getPosition();
        //setters
        void setSize(sf::Vector2i);
        void setPosition(sf::Vector2f);
        //functions
    protected:
        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::Vector2i size;
        sf::Vector2f position;  //maybe both vector2f?
    private:
};

#endif // DRAWABLE_H

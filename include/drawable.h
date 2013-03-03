#ifndef DRAWABLE_H
#define DRAWABLE_H

//only used for things that are drawn to a lot, since RenderTextures have high memory usage.

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
    private:
};

#endif // DRAWABLE_H

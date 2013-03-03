#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

//used for objects that are created in high amounts AND require editing/drawing multiple things. To save memory usage, only 1 rendertexture for all objects is used.

class Entity
{
    public:
        //ctor/dtor
        Entity(sf::RenderTexture*, sf::Sprite*);
        virtual ~Entity();
        //getters
        sf::Vector2f getPosition();
        //setters
        void setPosition(sf::Vector2f);
        //functions
        virtual void draw(sf::RenderTexture*) = 0;
    protected:
        sf::RenderTexture * canvas; //renderTextures use too much ram to have one for each object
        sf::Sprite * drawable;
        sf::Vector2f position;
    private:
};

#endif // ENTITY_H

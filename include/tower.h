#ifndef TOWER_H
#define TOWER_H
#include "global.h"
#include <cmath>

class Tower
{
    public:
        Tower();
        virtual ~Tower();
        //getters
        double getRotation();
        sf::Vector2i getCoordinates();
        static sf::Vector2i getSize();
        int getRange();
        //setters
        void setRotation(double);
        void setRotationTarget(sf::Vector2f);
        void setCoordinates(sf::Vector2i);
        //functions
        void update();
        void draw(sf::RenderTarget*);
    protected:
    private:
        //vars
        sf::RectangleShape base;    //40x40 base
        sf::RectangleShape turret;  //40x40 turret, can spin around (use transparent image to make smaller visual turret)
        sf::Texture baseTexture;
        sf::Texture turretTexture;
        sf::Vector2i coordinates;
        sf::Vector2f position;

        int range;
};

#endif // TOWER_H

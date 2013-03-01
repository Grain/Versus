#ifndef TOWER_H
#define TOWER_H

#include <Drawable.h>
#include "global.h"


class Tower : public Drawable
{
    public:
        Tower();
        virtual ~Tower();
        //getters
        float getRotation();
        sf::Vector2i getCoordinates();
        //setters
        void setRotation(float);
        void setCoordinates(sf::Vector2i);
        //functions
        void update();
    protected:
    private:
        //vars
        sf::RectangleShape base;    //40x40 base
        sf::RectangleShape turret;  //40x40 turret, can spin around (use transparent image to make smaller visual turret)
        sf::Vector2i coordinates;
};

#endif // TOWER_H

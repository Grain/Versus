#ifndef TOWER_H
#define TOWER_H
#include "global.h"


class Tower
{
    public:
        Tower();
        virtual ~Tower();
        //getters
        double getRotation();
        sf::Vector2i getCoordinates();
        static sf::Vector2i getSize();
        //setters
        void setRotation(double);
        void setCoordinates(sf::Vector2i);
        //functions
        void update();
        void draw(sf::RenderTarget*);
    protected:
    private:
        //vars
        sf::RectangleShape base;    //40x40 base
        sf::RectangleShape turret;  //40x40 turret, can spin around (use transparent image to make smaller visual turret)
        sf::Vector2i coordinates;
        sf::Vector2f position;
};

#endif // TOWER_H

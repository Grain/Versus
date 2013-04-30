#ifndef TOWER_H
#define TOWER_H
#include "global.h"
#include "creep.h"
#include "projectile.h"
#include <cmath>
#include <vector>

class Projectile;    //forward declaration

class Tower
{
    public:
        //ctor/dtor
        Tower(std::vector<Creep*>*, int);
        Tower();
        virtual ~Tower();
        //getters
        double getRotation();
        sf::Vector2i getCoordinates();
        static sf::Vector2i getSize();
        int getRange();
        Creep * getTarget();
        sf::Vector3i getType();
        //setters
        void setRotation(double);
        void setRotationTarget(sf::Vector2f);
        void setCoordinates(sf::Vector2i);
        //functions
        Projectile * update();
        void draw(sf::RenderTarget*);
        void upgrade(int);
    protected:
    private:
        //functions
        void updateStats();

        //vars
        sf::RectangleShape base;    //40x40 base
        sf::RectangleShape turret;  //40x40 turret, can spin around (use transparent image to make smaller visual turret)
        sf::Texture baseTexture;
        sf::Texture turretTexture;
        sf::Vector2i coordinates;
        sf::Vector2f position;
        sf::Vector3i type;  //x = primary (1-3), y = secondary(1-3), z = upgrade level(0-9)

        std::vector<Creep*> * creeps;
        Creep * target;
        Stats stats;
        int rateCount;
};

#endif // TOWER_H

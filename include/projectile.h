#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "creep.h"
#include "tower.h"

class Tower;    //forward declaration

class Projectile
{
    public:
        //ctor/dtor
        Projectile(Creep*, std::vector<Creep*>*, Tower*, sf::Vector2f);
        Projectile();
        virtual ~Projectile();
        //getters
        bool isDead();
        //functions
        void update();
        void draw(sf::RenderTarget*);
    protected:
    private:
        Creep * target;
        std::vector<Creep*> * creeps;
        Tower * tower;
        bool dead;

        sf::RectangleShape image;

        double speed;   //actual speed is this * 4
        int damage;
};

#endif // PROJECTILE_H
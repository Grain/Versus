#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "creep.h"

class Projectile
{
    public:
        //ctor/dtor
        Projectile(Creep*, sf::Vector2f);
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
        bool dead;

        sf::RectangleShape image;

        double speed;
        int damage;
};

#endif // PROJECTILE_H

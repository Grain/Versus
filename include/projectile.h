#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "creep.h"
#include "tower.h"

class Tower;    //forward declaration

class Projectile
{
    public:
        //ctor/dtor
        Projectile(Creep*, std::vector<Creep*>*, Tower*, sf::Vector2f, int, int, double, int, bool);
        Projectile();
        virtual ~Projectile();
        //getters
        int getType();
        bool isDead();
        //setters
        void setTextures(sf::Texture*, sf::Texture*);
        //functions
        void update();
        void draw(sf::RenderTarget*);
    protected:
    private:
        Creep * target;
        std::vector<Creep*> * creeps;
        Tower * tower;
        bool dead;
        bool animate;
        int animation;

        sf::Vector2f graphicSize;       //stuff for the picture that appears when the projectile is destroyed (an explosion, particles, etc.)
        sf::Texture * graphicTexture;

        sf::RectangleShape image;
        sf::Texture * texture;

        double speed;   //actual speed is this * 4
        int damage;
        int type;
        int range;
        bool homing;
};

#endif // PROJECTILE_H

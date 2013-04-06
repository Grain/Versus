#ifndef CREEP_H
#define CREEP_H

#include "global.h"

class Creep
{
    public:
        Creep(int [][GRIDY], int);
        Creep();
        virtual ~Creep();
        void draw(sf::RenderTarget*);
        void update();
        sf::Vector2i getCoordinates();

        bool isDead();
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;

        int (*distances) [GRIDY];
        int side;
        bool dead;
        sf::RectangleShape body;
        sf::Vector2f targetPoint;
        sf::Vector2i coordinates;
        sf::Vector2i enemy;

        int maxHp;
        int hp;
        double speed;   //actual speed is 2*speed pixels/sec

        sf::Texture bodyTexture;
        int animation;
};

#endif // CREEP_H

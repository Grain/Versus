#ifndef CREEP_H
#define CREEP_H

#include "global.h"

class Creep
{
    public:
        Creep(int [][GRIDY]);
        Creep();
        virtual ~Creep();
        void draw(sf::RenderTarget*);
        void update();
        sf::Vector2i getCoordinates();
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;

        int (*distances) [GRIDY];
        sf::RectangleShape body;
        sf::Vector2f targetPoint;
        sf::Vector2i coordinates;
};

#endif // CREEP_H

#ifndef TOWER_H
#define TOWER_H

#include <Drawable.h>


class Tower : public Drawable
{
    public:
        Tower();
        virtual ~Tower();
        //getters
        float getRotation();
        //setters
        void setRotation(float);
        //functions
        void update();
    protected:
    private:
        //vars
        sf::RectangleShape base;    //40x40 base
        sf::RectangleShape turret;  //40x40 turret, can spin around (use transparent image to make smaller visual turret)
};

#endif // TOWER_H

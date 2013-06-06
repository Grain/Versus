#ifndef CREEP_H
#define CREEP_H

#include "global.h"

class Creep
{
    public:
        //ctor/dtor
        Creep(int [][GRIDY], int, int, int, int, sf::Texture*, sf::Texture*, sf::Texture*, sf::Texture*, sf::Texture*, sf::Texture*, int);
        Creep();
        virtual ~Creep();
        //getters
        sf::Vector2i getCoordinates();
        sf::Vector2f getPosition();
        sf::Vector2i getProgress();
        sf::FloatRect getGlobalBounds();
        bool isDead();

        //functions
        void damage(int);
        void heal(int);
        void draw(sf::RenderTarget*);
        int update();
        void buff(int, int);
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;
        static const int HEALTHHEIGHT = 2;
        static const int HEALTHDISTANCE = 3;    //distance between health bar and actual creep

        int (*distances) [GRIDY];
        int side;
        bool dead;
        sf::RectangleShape body;
        sf::Vector2f targetPoint;
        sf::Vector2i coordinates;
        sf::Vector2i enemy;
        int bigProgress;   //distance from the pathfinding grid
        double smallProgress;   //distnace to target

        sf::Vector2i buffs[5];   //x = time, y = severity of buff
        //0 = damage amp, 1 = slow, 2 = damage reduction, 3 = regen, 4 = speed
        sf::Texture * buffTextures[5];
        sf::RectangleShape buffIcons[5];

        int maxHp;
        int hp;
        double speed;   //actual speed is 2*speed pixels/sec
        int type;   //0 normal, 1 speed, 2 tank, 3 flying

        sf::Texture * bodyTexture;
        int animation;

        sf::RectangleShape health;
        sf::RectangleShape healthOutline;
};

#endif // CREEP_H

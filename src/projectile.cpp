#include "projectile.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Projectile::Projectile(Creep * temp, sf::Vector2f pos)
{
    target = temp;

    image.setFillColor(sf::Color::Black);
    image.setPosition(pos);
    image.setSize({5, 5});

    dead = false;

    speed = 1;
    damage = 20;
}

Projectile::Projectile()
{
    //ctor
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Projectile::~Projectile()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

bool Projectile::isDead()
{
    return dead;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Projectile::update()
{
    if (target->isDead())
    {
        dead = true;
        return;
    }

    for (int i = 0; i < 4; ++i)     //for better collision detection resolution
    {
        if (image.getGlobalBounds().intersects(target->getGlobalBounds()))
        {
            target->damage(damage);
            dead = true;
            return;
        }

        double ratio = speed / distance(image.getPosition(), target->getPosition());
        image.move((target->getPosition().x - image.getPosition().x) * ratio, (target->getPosition().y - image.getPosition().y) * ratio);
    }
}

void Projectile::draw(sf::RenderTarget * renderTarget)
{
    renderTarget->draw(image);
}

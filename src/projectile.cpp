#include "projectile.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Projectile::Projectile(Creep * tempTarget, std::vector<Creep*>* tempCreeps, Tower* tempTower, sf::Vector2f pos, int tempType, int tempDamage, double tempSpeed)
{
    target = tempTarget;
    creeps = tempCreeps;
    tower = tempTower;

    image.setFillColor(sf::Color::Black);
    image.setPosition(pos);
    image.setSize({5, 5});

    dead = false;
    homing = true;

    speed = tempSpeed;
    type = tempType;
    damage = tempDamage;
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
        if (homing == false)
        {
            dead = true;
            return;
        }

        bool newTarget = true;

        if (tower->getTarget() != NULL)     //parent tower has another valid target
        {
            if (tower->getTarget()->isDead() == false)
            {
                target = tower->getTarget();
                newTarget = false;
            }
        }

        if (newTarget)          //parent tower has no target
        {
            if (creeps->size() > 0)     //parent tower has no target, so just target the oldest creep alive
            {
                bool hasTarget = false;

                for(unsigned int i = 0; i < creeps->size(); ++i)
                {
                    if ((*creeps)[i]->isDead() == false)    //found an alive creep!
                    {
                        target = (*creeps)[i];
                        hasTarget = true;
                        break;
                    }
                }

                if (hasTarget == false)
                {
                    dead = true;
                    return;
                }
            }
            else        //parent tower has no target, and there are no creeps alive at all
            {
                dead = true;
                return;
            }
        }
    }

    for (int i = 0; i < 4; ++i)     //for better collision detection resolution
    {
        if (image.getGlobalBounds().intersects(target->getGlobalBounds()))      //HIT!
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

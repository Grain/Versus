#include "projectile.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Projectile::Projectile(Creep * tempTarget, std::vector<Creep*>* tempCreeps, Tower* tempTower, sf::Vector2f pos, int tempType, int tempDamage, double tempSpeed, int tempRange, bool tempHoming)
{
    target = tempTarget;
    creeps = tempCreeps;
    tower = tempTower;

    switch(tempType)
    {
        case 0: //basic 1
            image.setSize({5, 5});
            graphicSize = {10, 10};
            break;
        case 1: //1.1
            image.setSize({2, 5});  //machine gun tower
            graphicSize = {5, 5};
            break;
        case 2: //1.2
            image.setSize({4, 4});      //normal
            graphicSize = {10, 10};
            break;
        case 3: //1.3
            image.setSize({10, 10});    //buff tower
            graphicSize = {10, 10};
            break;
        case 4: //basic 2
            image.setSize({5, 10});     //missile
            graphicSize = {10, 10};
            break;
        case 5: //2.1
            image.setSize({2, 40});      //snipa
            graphicSize = {10, 10};
            break;
        case 6: //2.2
            image.setSize({10, 20});      //aoe missile
            graphicSize = {50, 50};
            break;
        case 7: //2.3
            image.setSize({5, 10});          //heal missile
            graphicSize = {50, 50};
            break;
        case 8: //basic 3
            image.setSize({4, 4});
            graphicSize = {120, 120};
            break;
        case 9: //2.1                           //slow
            image.setSize({4, 4});
            graphicSize = {120, 120};
            break;
        case 10: //2.2
            image.setSize({4, 4});              //damage amp
            graphicSize = {120, 120};
            break;
        case 11: //2.3
            image.setSize({4, 4});              //damage
            graphicSize = {120, 120};
            break;
    }

    char temp[40];
    sprintf(temp, "resources/explosion%d.png", tempType);
    graphicTexture.loadFromFile(temp);
    sprintf(temp, "resources/projectile%d.png", tempType);
    texture.loadFromFile(temp);

    image.setTexture(&texture);
    image.setPosition(pos);
    image.setOrigin(image.getSize().x / 2, image.getSize().y / 2);

    dead = false;
    animate = false;
    animation = 0;

    range = tempRange;
    homing = tempHoming;
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
    if (animate == true)
    {
        if (animation > graphicTexture.getSize().x - graphicSize.x)
        {
            dead = true;
            return;
        }
        image.setTextureRect(sf::IntRect(animation, 0, graphicSize.x, graphicSize.y));
        animation += graphicSize.x;
    }
    else
    {
        if (type >= 8)  //splash tower
        {
            for(unsigned int i = 0; i < creeps->size(); ++i)
            {
                if ((*creeps)[i]->isDead() == false)
                {
                    if (distance(image.getPosition(), (*creeps)[i]->getPosition()) < range)
                    {
                        //hit!
                        if (type == 8)  //base
                        {
                            (*creeps)[i]->damage(damage);
                        }
                        else if (type == 9) //slow
                        {
                            (*creeps)[i]->buff(1, damage);
                        }
                        else if (type == 10)    //damage amp
                        {
                            (*creeps)[i]->buff(0, damage);
                        }
                        else    //damage
                        {
                            (*creeps)[i]->damage(damage);
                        }
                    }
                }
            }

            animate = true;
            image.setSize(graphicSize);
            image.setOrigin(graphicSize.x / 2, graphicSize.y / 2);
            image.setTexture(&graphicTexture);
            return;
        }
        else
        {
            if (target->isDead())
            {
                if (homing == false)
                {
                    animate = true;
                    image.setSize(graphicSize);
                    image.setOrigin(graphicSize.x / 2, graphicSize.y / 2);
                    image.setTexture(&graphicTexture);
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
                            animate = true;
                            image.setSize(graphicSize);
                            image.setOrigin(graphicSize.x / 2, graphicSize.y / 2);
                            image.setTexture(&graphicTexture);
                            return;
                        }
                    }
                    else        //parent tower has no target, and there are no creeps alive at all
                    {
                        animate = true;
                        image.setSize(graphicSize);
                        image.setOrigin(graphicSize.x / 2, graphicSize.y / 2);
                        image.setTexture(&graphicTexture);
                        return;
                    }
                }
            }

            //hitting creeps
            for (int i = 0; i < 4; ++i)     //for better collision detection resolution
            {
                if (image.getGlobalBounds().intersects(target->getGlobalBounds()))      //HIT!
                {
                    //TODO: different effects here
                    switch(type)
                    {
                        case 0:
                        case 1:
                        case 2:
                        case 4:
                        case 5:
                            target->damage(damage);
                            break;
                        case 3:
                            //buff
                            target->buff(rand() % 3 + 2, damage);
                            break;
                        case 6:     //aoe missile
                            for(unsigned int a = 0; a < creeps->size(); ++a)
                            {
                                if ((*creeps)[a]->isDead() == false)
                                {
                                    if (distance(image.getPosition(), (*creeps)[a]->getPosition()) < range)
                                    {
                                        //hit!
                                        (*creeps)[a]->damage(damage);
                                    }
                                }
                            }
                            break;
                        case 7: //aoe heal missile
                            for(unsigned int a = 0; a < creeps->size(); ++a)
                            {
                                if ((*creeps)[a]->isDead() == false)
                                {
                                    if (distance(image.getPosition(), (*creeps)[a]->getPosition()) < range)
                                    {
                                        //hit!
                                        (*creeps)[a]->heal(damage);
                                    }
                                }
                            }
                            break;
                    }
                    animate = true;
                    image.setSize(graphicSize);
                    image.setOrigin(graphicSize.x / 2, graphicSize.y / 2);
                    image.setTexture(&graphicTexture);
                    return;
                }

                double ratio = speed / distance(image.getPosition(), target->getPosition());
                image.move((target->getPosition().x - image.getPosition().x) * ratio, (target->getPosition().y - image.getPosition().y) * ratio);

                //rotate
                double angle = atan((target->getPosition().x - image.getPosition().x)/(image.getPosition().y - target->getPosition().y)) * 180 / 3.14159265;
                if(image.getPosition().y - target->getPosition().y < 0)
                    angle += 180;
                image.setRotation(angle);
            }
        }
    }
}

void Projectile::draw(sf::RenderTarget * renderTarget)
{
    renderTarget->draw(image);
}

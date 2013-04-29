#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower(std::vector<Creep*>* temp, int baseType)
{
    base.setSize((sf::Vector2f)Tower::getSize());
    turret.setSize((sf::Vector2f)Tower::getSize());
    turret.setOrigin(Tower::getSize().x / 2, Tower::getSize().y / 2);

    turretTexture.loadFromFile("resources/turret.png");
    turret.setTexture(&turretTexture);

    base.setFillColor(sf::Color::Blue); //temp, need pictures

    range = 100;

    creeps = temp;
    target = NULL;
    rate = 1;
    rateCount = rate;
    damage = 30;

    type = {baseType + 1, 0, 0};
}

Tower::Tower()
{

}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Tower::~Tower()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

double Tower::getRotation()
{
    return turret.getRotation();
}

sf::Vector2i Tower::getCoordinates()
{
    return coordinates;
}

sf::Vector2i Tower::getSize()
{
    return {BOXDIMENSIONS, BOXDIMENSIONS};
}

int Tower::getRange()
{
    return range;
}

Creep * Tower::getTarget()
{
    return target;
}

sf::Vector3i Tower::getType()
{
    return type;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Tower::setRotation(double i)
{
    turret.setRotation(i);
}

void Tower::setRotationTarget(sf::Vector2f i)
{
    sf::Vector2f center = {position.x + Tower::getSize().x / 2, position.y + Tower::getSize().y / 2};
    double angle = atan((i.x - center.x)/(center.y - i.y)) * 180 / 3.14159265;
    if(center.y - i.y < 0)
        angle += 180;
    turret.setRotation(angle);
}

void Tower::setCoordinates(sf::Vector2i i)
{
    coordinates = i;
    position = (sf::Vector2f)coordinatePosition(i);
    base.setPosition(position);
    turret.setPosition(position.x + Tower::getSize().x / 2, position.y + Tower::getSize().y / 2);
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

Projectile * Tower::update()
{
    bool hasTarget = false;

    for (unsigned int i = 0; i < creeps->size(); ++i)
    {
        if (distance((*creeps)[i]->getPosition(), turret.getPosition()) < range)
        {
            hasTarget = true;

            if (target == NULL)
            {
                target = (*creeps)[i];
            }
            else
            {
                if ((*creeps)[i]->getProgress().x < target->getProgress().x)
                {
                    target = (*creeps)[i];
                }
                else if ((*creeps)[i]->getProgress().x == target->getProgress().x)
                {
                    if ((*creeps)[i]->getProgress().y < target->getProgress().y)
                    {
                        target = (*creeps)[i];
                    }
                }
            }
        }
    }

    if (hasTarget == false)
    {
        target = NULL;
    }

    if (rateCount > 0)
        rateCount--;

    if (target != NULL)
    {
        if (target->isDead())
        {
            target = NULL;
            return NULL;
        }

        setRotationTarget(target->getPosition());
        if (rateCount == 0)
        {
            rateCount = rate;
            return new Projectile(target, creeps, this, turret.getPosition());
        }
    }

    return NULL;
}

void Tower::draw(sf::RenderTarget * target)
{
    target->draw(base);
    target->draw(turret);
}

void Tower::upgrade(int i)
{
    if (type.y == 0)
    {
        type.y = i;
    }
    else
    {
        if (i == 1) //first button pressed, since there is only 1 upgrade available at this point
        {
            type.z++;   //TODO: limit for upgrade level
        }
    }

    updateStats();
}

void Tower::updateStats()
{
    //gogogo need 3d array of stats and a struct for stats
    range = 100 + 30 * type.z;
}

#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower(std::vector<Creep*>* tempEnemies, std::vector<Creep*>* tempAllies, int baseType, sf::Texture * tempBase, sf::Texture * tempTurret, sf::Texture * temp1, sf::Texture * temp2, sf::Texture * temp3)
{
    base.setSize((sf::Vector2f)Tower::getSize());
    turret.setSize((sf::Vector2f)Tower::getSize());
    soldOverlay.setSize((sf::Vector2f)Tower::getSize());
    turret.setOrigin(Tower::getSize().x / 2, Tower::getSize().y / 2);
    level.setSize({5, 19});
    level.setOrigin(level.getSize());
    baseTexture = tempBase;
    base.setTexture(baseTexture);
    turretTexture = tempTurret;
    turret.setTexture(turretTexture);

    soldOverlay.setFillColor(sf::Color(0, 0, 0, 128));

    turret.setRotation(rand() % 360);

    levelTexture[0] = temp1;
    levelTexture[1] = temp2;
    levelTexture[2] = temp3;

    enemies = tempEnemies;
    allies = tempAllies;

    target = NULL;

    type = {baseType + 1, 0, 0};
    stats = towerStats[type.x - 1][type.y][type.z];

    rateCount = stats.fireRate;
    totalCost = stats.cost;

    sold = false;

    if (stats.type >= 8)
    {
        aoe = stats.range;
    }
    else
    {
        aoe = 40;   //const
    }
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
    return stats.range;
}

Creep * Tower::getTarget()
{
    return target;
}

sf::Vector3i Tower::getType()
{
    return type;
}

std::string Tower::getCurrentInfo()
{
    std::string temp1("");
    char temp2[200];
    sprintf(temp2, "%s", descriptions[stats.type].c_str());
    temp1 += temp2;
    if (stats.type == 3)        //buff tower
    {
        sprintf(temp2, "Buff amount: %d\n", stats.damage);
    }
    else if (stats.type == 7)       //aoe heal missile
    {
        sprintf(temp2, "Amount healed: %d\n", stats.damage);
    }
    else if (stats.type == 9)       //splash slow
    {
        sprintf(temp2, "Slow: %d%%\n", stats.damage);
    }
    else if (stats.type == 10)       //splash damage amp
    {
        sprintf(temp2, "Damage amplification:\n%d%%\n", stats.damage);
    }
    else
    {
        sprintf(temp2, "Damage: %d\n", stats.damage);
    }
    temp1 += temp2;
    sprintf(temp2, "Fire rate: %.1f / second\nRange: %d\n", (double)FPS / stats.fireRate, stats.range);
    temp1 += temp2;

    if (stats.type < 8)    //not splash tower, put speed
    {
        sprintf(temp2, "Projectile speed: %.1f", stats.speed);
        temp1 += temp2;
    }
    return temp1;
}

std::string Tower::getUpgradeInfo(int a)
{
    std::string temp1("");
    char temp2[200];
    if (a == 3) //sell
    {
        sprintf(temp2, "Sell for $%d", totalCost / 2);
        temp1 += temp2;
    }
    else   //upgrade
    {
        Stats tempStats;
        if (type.y == 0)    //changing to new subtype of tower, don't display the differences in stats
        {
            tempStats = towerStats[type.x - 1][a + 1][0];
            sprintf(temp2, "Cost: $%d\n\n", tempStats.cost);
            temp1 += temp2;
            sprintf(temp2, "%s", descriptions[tempStats.type].c_str());
            temp1 += temp2;
            if (tempStats.type == 3)        //buff tower
            {
                sprintf(temp2, "Buff amount: %d\n", tempStats.damage);
            }
            else if (tempStats.type == 7)       //aoe heal missile
            {
                sprintf(temp2, "Amount healed: %d\n", tempStats.damage);
            }
            else if (tempStats.type == 9)       //splash slow
            {
                sprintf(temp2, "Slow: %d%%\n", tempStats.damage);
            }
            else if (tempStats.type == 10)       //splash damage amp
            {
                sprintf(temp2, "Damage amplification:\n%d%%\n", tempStats.damage);
            }
            else
            {
                sprintf(temp2, "Damage: %d\n", tempStats.damage);
            }
            temp1 += temp2;

            sprintf(temp2, "Fire rate: %.1f / second\nRange: %d\n", (double)FPS / tempStats.fireRate, tempStats.range);
            temp1 += temp2;

            if (stats.type < 8)    //not splash tower, put speed
            {
                sprintf(temp2, "Projectile speed: %.1f", tempStats.speed);
                temp1 += temp2;
            }
        }
        else
        {
            if (a == 0) //pressed the upgrade button
            {
                if (type.z < 3)     //upgrading tower level, display the change in stats
                {
                    tempStats = towerStats[type.x - 1][type.y][type.z + 1];
                    sprintf(temp2, "Cost: $%d\n\n", tempStats.cost);
                    temp1 += temp2;
                    sprintf(temp2, "%s", descriptions[tempStats.type].c_str());
                    temp1 += temp2;
                    if (tempStats.type == 3)        //buff tower
                    {
                        sprintf(temp2, "Buff amount: %d (+%d)\n", tempStats.damage, tempStats.damage - stats.damage);
                    }
                    else if (tempStats.type == 7)       //aoe heal missile
                    {
                        sprintf(temp2, "Amount healed: %d (+%d)\n", tempStats.damage, tempStats.damage - stats.damage);
                    }
                    else if (tempStats.type == 9)       //splash slow
                    {
                        sprintf(temp2, "Slow: %d%% (+%d%%)\n", tempStats.damage, tempStats.damage - stats.damage);
                    }
                    else if (tempStats.type == 10)       //splash damage amp
                    {
                        sprintf(temp2, "Damage amplification:\n%d%% (+%d%%)\n", tempStats.damage, tempStats.damage - stats.damage);
                    }
                    else
                    {
                        sprintf(temp2, "Damage: %d (+%d)\n", tempStats.damage, tempStats.damage - stats.damage);
                    }
                    temp1 += temp2;

                    sprintf(temp2, "Fire rate: %.1f / second (+%.1f)\nRange: %d (+%d)\n", (double)FPS / tempStats.fireRate, (double)FPS / tempStats.fireRate - (double)FPS / stats.fireRate, tempStats.range, tempStats.range - stats.range);
                    temp1 += temp2;

                    if (stats.type < 8)    //not splash tower, put speed
                    {
                        sprintf(temp2, "Projectile speed: %.1f", tempStats.speed);
                        temp1 += temp2;
                    }
                }
            }
        }
    }
    return temp1;
}

bool Tower::isSold()
{
    return sold;
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
    level.setPosition(position + (sf::Vector2f)Tower::getSize() - (sf::Vector2f){1, 1});
    soldOverlay.setPosition(base.getPosition());
}

void Tower::setTextures(sf::Texture * tempBase, sf::Texture * tempTurret)
{
    baseTexture = tempBase;
    turretTexture = tempTurret;

    base.setTexture(baseTexture);
    turret.setTexture(turretTexture);
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

Projectile * Tower::update()
{
    if (sold)
    {
        return NULL;
    }

    std::vector<Creep*> * temp;
    if ((type.x == 1 && type.y == 3) || (type.x == 2 && type.y == 3))
    {
        temp = allies;
    }
    else
    {
        temp = enemies;
    }

    bool hasTarget = false;

    if (target != NULL)
    {
        if (target->isDead() == false)
        {
            if (distance(target->getPosition(), turret.getPosition()) > stats.range)
            {
                target = NULL;      //target out of range
            }
        }
    }

    for (unsigned int i = 0; i < temp->size(); ++i)
    {
        if (distance((*temp)[i]->getPosition(), turret.getPosition()) < stats.range)
        {
            hasTarget = true;

            if (target == NULL)
            {
                target = (*temp)[i];
            }
            else
            {
                if ((*temp)[i]->getProgress().x < target->getProgress().x)
                {
                    target = (*temp)[i];
                }
                else if ((*temp)[i]->getProgress().x == target->getProgress().x)
                {
                    if ((*temp)[i]->getProgress().y < target->getProgress().y)
                    {
                        target = (*temp)[i];
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
            rateCount = stats.fireRate;
            return new Projectile(target, temp, this, turret.getPosition(), stats.type, stats.damage, stats.speed, aoe, stats.homing);
        }
    }

    return NULL;
}

void Tower::draw(sf::RenderTarget * target)
{
    target->draw(base);
    target->draw(turret);

    if (type.z > 0)
    {
        target->draw(level);
    }

    if (sold)
    {
        target->draw(soldOverlay);
    }
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
            type.z++;
            level.setTexture(levelTexture[type.z - 1]);
        }
    }

    updateStats();
}

void Tower::updateStats()
{
    stats = towerStats[type.x - 1][type.y][type.z];

    if (stats.type >= 8)
    {
        aoe = stats.range;
    }
    else
    {
        aoe = 40;   //const
    }

    totalCost = 0;
    totalCost += towerStats[type.x - 1][0][0].cost;
    if (type.y > 0)
    {
        totalCost += towerStats[type.x - 1][type.y][0].cost;
        for(int i = type.z; i > 0; --i)
        {
            totalCost += towerStats[type.x - 1][type.y][i].cost;
        }
    }
}

int Tower::sell()
{
    sold = true;
    return totalCost / 2;
}

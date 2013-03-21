#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower()
{
    base.setSize((sf::Vector2f)Tower::getSize());
    turret.setSize((sf::Vector2f)Tower::getSize());
    turret.setOrigin(Tower::getSize().x / 2, Tower::getSize().y / 2);
    turret.setPosition(Tower::getSize().y / 2, Tower::getSize().y / 2);

    base.setFillColor(sf::Color::Blue); //temp, need pictures
    turret.setFillColor(sf::Color::Red);
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

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Tower::setRotation(double i)
{
    turret.setRotation(i);
}

void Tower::setCoordinates(sf::Vector2i i)
{
    static const int gridSize = BOXDIMENSIONS + 1; //grid box + border
    coordinates = i;
    position = {(float)(gridSize + i.x * gridSize), (float)(1 + i.y * gridSize)};
    base.setPosition(position);
    turret.setPosition(position.x + Tower::getSize().y / 2, position.y + Tower::getSize().y / 2);
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Tower::update()
{

}

void Tower::draw(sf::RenderTarget * target)
{
    target->draw(base);
    target->draw(turret);
}

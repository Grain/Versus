#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower()
{
    base.setSize((sf::Vector2f)Tower::getSize());
    turret.setSize((sf::Vector2f)Tower::getSize());
    turret.setOrigin(Tower::getSize().x / 2, Tower::getSize().y / 2);

    turretTexture.loadFromFile("resources/turret.png");
    turret.setTexture(&turretTexture);

    base.setFillColor(sf::Color::Blue); //temp, need pictures
    //turret.setFillColor(sf::Color::Red);
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

void Tower::update()
{

}

void Tower::draw(sf::RenderTarget * target)
{
    target->draw(base);
    target->draw(turret);
}

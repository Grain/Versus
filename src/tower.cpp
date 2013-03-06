#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower(sf::RenderTexture* a, sf::Sprite* b) : Entity(a, b)
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

float Tower::getRotation()
{
    return turret.getRotation();
}

sf::Vector2i Tower::getCoordinates()
{
    return coordinates;
}

sf::Vector2i Tower::getSize()
{
    return {40, 40};
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Tower::setRotation(float i)
{
    turret.setRotation(i);
}

void Tower::setCoordinates(sf::Vector2i i)
{
    const int gridSize = 41; //grid box + border
    coordinates = i;
    position = {(float)(gridSize + i.x * gridSize), (float)(1 + i.y * gridSize)};
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Tower::update()
{

}

void Tower::draw(sf::RenderTexture * target)
{
    canvas->clear(sf::Color::Transparent);
    canvas->draw(base);
    canvas->draw(turret);
    canvas->display();
    drawable->setPosition(position);
    drawable->setTexture(canvas->getTexture());
    target->draw(*drawable);
}

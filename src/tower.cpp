#include "tower.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Tower::Tower()
{
    size = {40, 40};
    base.setSize({40, 40});
    turret.setSize({40, 40});   //consts
    turret.setOrigin(turret.getSize().x / 2, turret.getSize().y / 2);
    turret.setPosition((float)base.getSize().y / (float)2, (float)base.getSize().y / (float)2);

    canvas.create(size.x, size.y);

    base.setFillColor(sf::Color::Blue); //temp, need pictures
    turret.setFillColor(sf::Color::Red);

    canvas.clear(sf::Color::Transparent);

    canvas.draw(base);
    canvas.draw(turret);

    canvas.display();
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

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Tower::setRotation(float i)
{
    turret.setRotation(i);
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Tower::update()
{
    canvas.clear(sf::Color::Transparent);

    canvas.draw(base);
    canvas.draw(turret);

    canvas.display();
}

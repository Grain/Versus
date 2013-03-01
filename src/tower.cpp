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

    if(!canvas.create(size.x, size.y))
        printf("Error in creating tower\n");    //maybe output identification of tower?

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

sf::Vector2i Tower::getCoordinates()
{
    return coordinates;
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
    canvas.clear(sf::Color::Transparent);

    canvas.draw(base);
    canvas.draw(turret);

    canvas.display();
}

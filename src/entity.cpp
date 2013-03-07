#include "entity.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Entity::Entity(sf::RenderTexture* a, sf::Sprite* b)
{
    canvas = a;
    drawable = b;
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Entity::~Entity()
{
    //dtor
}
/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

sf::Vector2f Entity::getPosition()
{
    return position;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Entity::setPosition(sf::Vector2f i)
{
    position = i;
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/
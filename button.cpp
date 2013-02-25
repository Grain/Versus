#include "button.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Button::Button()
{
    w = 100;
    h = 50;
    x = 0;
    y = 0;
    bgColor = sf::Color::Black;
    fgColor = sf::Color::White;
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Button::~Button()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

inline int Button::getWidth()
{
    return w;
}
inline int Button::getHeight()
{
    return h;
}
inline int Button::getTop()
{
    return y;
}
inline int Button::getLeft()
{
    return x;
}
inline int Button::getRight()
{
    return x+w;
}
inline int Button::getBottom()
{
    return y+h;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Button::setWidth(int i)
{
    w = i;
}

void Button::setHeight(int i)
{
    h = i;
}

void Button::setDim(int a, int b)
{
    w = a;
    h = b;
}

void Button::setPos(int a, int b)
{
    x = a;
    y = b;
}

void Button::setColor(sf::Color fg, sf::Color bg)
{
    fgColor = fg;
    bgColor = bg;
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

bool Button::contains(sf::Vector2i pos)
{
    if (pos.x < getLeft() || pos.x > getRight() ||
        pos.y < getTop() || pos.y > getBottom() )
    { return false; }
    return true;
}


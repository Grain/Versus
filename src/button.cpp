#include "button.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Button::Button()
{
    visible = true;
    downed = false;
    prevState = false;
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

sf::Vector2f Button::getSize()
{
    return rect.getSize();
}

sf::Vector2f Button::getPosition()
{
    return rect.getPosition();
}

bool Button::getVisible()
{
    return visible;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Button::setPosition(sf::Vector2f i)
{
    rect.setPosition(i);
}

void Button::setVisible(bool i)
{
    visible = i;
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Button::initialize(int a, int b)
{
    rect.setSize({(float)a, (float)b});
    normal.create(a, b);
    mouseOver.create(a, b);
    mouseDown.create(a, b);
}

void Button::loadTexture(std::string i)
{
    normal.loadFromFile(i, sf::IntRect(0, 0, rect.getSize().x, rect.getSize().y));
    mouseOver.loadFromFile(i, sf::IntRect(rect.getSize().x * 1, 0, rect.getSize().x, rect.getSize().y));
    mouseDown.loadFromFile(i, sf::IntRect(rect.getSize().x * 2, 0, rect.getSize().x, rect.getSize().y));
}

bool Button::update(sf::Vector2i mousePos)
{
    if(!visible)
        return false;

    bool temp = false;
    bool down = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    if (down)
    {
        if(inButton(mousePos) && prevState == false)    //mouse button was downed in button
        {
            downed = true;
            rect.setTexture(&mouseDown);
        }
    }
    else    //mouse is up
    {
        if(inButton(mousePos))
        {
            if(prevState == true && downed == true)
            {
                temp = true;    //mouse was downed in button and now raised in button
            }
            else
                rect.setTexture(&mouseOver);
        }
        else
        {
            rect.setTexture(&normal);
        }
        downed = false;
    }

    prevState = down;
    return temp;
}

void Button::draw(sf::RenderTarget* target)
{
    if(visible)
        target->draw(rect);
}

bool Button::inButton(sf::Vector2i i)
{
    return rect.getGlobalBounds().contains((sf::Vector2f)i);
}

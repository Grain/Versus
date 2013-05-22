#include "button.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Button::Button()
{
    visible = true;
    downed = false;
    prevState = false;
    hovered = false;
    usingCache = false;
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

bool Button::getHovered()
{
    return hovered;
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

void Button::setTexture(sf::Texture * i)
{
    usingCache = true;
    texturePointer = i; //only one because whenever i'm using cache, i never have mouseover/mousedown textures, it's always just one picture
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
    usingCache = false;
    normal.loadFromFile(i, sf::IntRect(0, 0, rect.getSize().x, rect.getSize().y));
    mouseOver.loadFromFile(i, sf::IntRect(rect.getSize().x * 1, 0, rect.getSize().x, rect.getSize().y));
    mouseDown.loadFromFile(i, sf::IntRect(rect.getSize().x * 2, 0, rect.getSize().x, rect.getSize().y));
}

bool Button::update(sf::Vector2i mousePos)
{
    if(!visible)
    {
        if (usingCache)
            rect.setTexture(texturePointer);
        else
            rect.setTexture(&normal);
        return false;
    }

    bool temp = false;
    bool down = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    inButton(mousePos);

    if (down)
    {
        if(hovered && prevState == false)    //mouse button was downed in button
        {
            downed = true;
            rect.setTexture(&mouseDown);
        }
    }
    else    //mouse is up
    {
        if(hovered)
        {
            if(prevState == true && downed == true)
            {
                temp = true;    //mouse was downed in button and now raised in button
            }
            else
            {
                rect.setTexture(&mouseOver);
            }
        }
        else
        {
            rect.setTexture(&normal);
        }
        downed = false;
    }

    prevState = down;

    if (usingCache)
    {
        rect.setTexture(texturePointer);
    }
    return temp;
}

void Button::draw(sf::RenderTarget* target)
{
    if(visible)
        target->draw(rect);
}

bool Button::inButton(sf::Vector2i i)
{
    hovered = rect.getGlobalBounds().contains((sf::Vector2f)i);
    return hovered;
}

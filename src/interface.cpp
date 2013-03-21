#include "interface.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Interface::Interface()  //todo: custom colours for selectors
{
    sf::Image temp;
    temp.loadFromFile("resources/selector.png");
    selector.loadFromImage(temp);
    temp.flipVertically();
    reflectedSelector.loadFromImage(temp);

    leftSelector.setSize({BOXDIMENSIONS, BOXDIMENSIONS});
    leftSelector.setTexture(&reflectedSelector);
    leftSelector.setFillColor(sf::Color::Cyan);
    leftCoordinates = {0, GRIDY / 2};

    rightSelector.setSize({BOXDIMENSIONS, BOXDIMENSIONS});
    rightSelector.setTexture(&selector);
    rightSelector.setFillColor(sf::Color::Magenta);
    rightCoordinates = {GRIDX * 2 + MIDDLE - 1, GRIDY / 2};

    prevMouse = {0, 0};

    prevLeft = prevRight = {false, false, false, false, false, false};
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Interface::~Interface()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/


/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/


/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

int Interface::update(sf::Vector2i mousePos)
{
    if (mousePos != prevMouse)  //todo: check for 2 player or no mouse option
    {
        //mouse things
    }

    static const int gridSize = BOXDIMENSIONS + 1; //grid box + border

    //temp, replace with custom key bindings soon

    //LEFT/////////////sure, i COULD use an array...
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (prevLeft.up == false)
            leftCoordinates.y -= 1;
        prevLeft.up = true;
    }
    else
    {
        prevLeft.up = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (prevLeft.down == false)
            leftCoordinates.y += 1;
        prevLeft.down = true;
    }
    else
    {
        prevLeft.down = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (prevLeft.left == false)
            leftCoordinates.x -= 1;
        prevLeft.left = true;
    }
    else
    {
        prevLeft.left = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (prevLeft.right == false)
            leftCoordinates.x += 1;
        prevLeft.right = true;
    }
    else
    {
        prevLeft.right = false;
    }

    if (leftCoordinates.y < 0)
        leftCoordinates.y = GRIDY - 1;
    if (leftCoordinates.y > GRIDY - 1)
        leftCoordinates.y = 0;
    if (leftCoordinates.x < 0)
        leftCoordinates.x = GRIDX * 2 + MIDDLE - 1;
    if (leftCoordinates.x > GRIDX * 2 + MIDDLE - 1)
        leftCoordinates.x = 0;

    leftSelector.setPosition((float)(gridSize + leftCoordinates.x * gridSize), (float)(1 + leftCoordinates.y * gridSize));

    //RIGHT/////////////
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (prevRight.up == false)
            rightCoordinates.y -= 1;
        prevRight.up = true;
    }
    else
    {
        prevRight.up = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (prevRight.down == false)
            rightCoordinates.y += 1;
        prevRight.down = true;
    }
    else
    {
        prevRight.down = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (prevRight.left == false)
            rightCoordinates.x -= 1;
        prevRight.left = true;
    }
    else
    {
        prevRight.left = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (prevRight.right == false)
            rightCoordinates.x += 1;
        prevRight.right = true;
    }
    else
    {
        prevRight.right = false;
    }

    if (rightCoordinates.y < 0)
        rightCoordinates.y = GRIDY - 1;
    if (rightCoordinates.y > GRIDY - 1)
        rightCoordinates.y = 0;
    if (rightCoordinates.x < 0)
        rightCoordinates.x = GRIDX * 2 + MIDDLE - 1;
    if (rightCoordinates.x > GRIDX * 2 + MIDDLE - 1)
        rightCoordinates.x = 0;

    rightSelector.setPosition((float)(gridSize + rightCoordinates.x * gridSize), (float)(1 + rightCoordinates.y * gridSize));

    return 0;
}

void Interface::draw(sf::RenderTarget* target)  //no double buffering (because it would be drawing on a buffer, then drawing that to Game class buffer)
{
    target->draw(leftSelector);
    target->draw(rightSelector);
}

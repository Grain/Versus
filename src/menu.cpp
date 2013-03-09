#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Menu::Menu()
{
    if (settings.doubleBuffered)
    {
        if(!canvas.create(XRES, YRES))
            printf("Error creating menu renderTexture\n");
    }

    background.setSize({XRES, YRES});
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::White);

    if(!backgroundTexture.create(XRES, YRES))
        printf("Error creating menu background\n");
    else
    {
        if(backgroundTexture.loadFromFile("resources/background.png"))
        {
            background.setTexture(&backgroundTexture);
        }
    }
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Menu::~Menu()
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

void Menu::draw(sf::RenderWindow * window)
{
    if (settings.doubleBuffered)
    {
        canvas.clear(sf::Color::Transparent);
        canvas.draw(background);
        canvas.display();
        drawable.setPosition(0, 0);
        drawable.setTexture(canvas.getTexture());
        window->draw(drawable);
    }
    else
    {
        window->draw(background);
    }
}


void Menu::update(sf::Vector2i mousePos)
{

}

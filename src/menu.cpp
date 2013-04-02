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

    backgroundTexture.loadFromFile("resources/menuBackground.png");
    background.setTexture(&backgroundTexture);

    mainMenu.push_back(new Button());   //single player
    mainMenu[0]->initialize(100, 50);
    mainMenu[0]->setPosition({100, 225});
    mainMenu[0]->loadTexture("resources/singlePlayer.png");

    mainMenu.push_back(new Button());   //multi player
    mainMenu[1]->initialize(100, 50);
    mainMenu[1]->setPosition({100, 300});
    mainMenu[1]->loadTexture("resources/multiPlayer.png");

    mainMenu.push_back(new Button());   //options
    mainMenu[2]->initialize(100, 50);
    mainMenu[2]->setPosition({100, 375});
    mainMenu[2]->loadTexture("resources/settings.png");

    mainMenu.push_back(new Button());   //exit button
    mainMenu[3]->initialize(100, 50);
    mainMenu[3]->setPosition({100, 450});
    mainMenu[3]->loadTexture("resources/exit.png");
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Menu::~Menu()
{
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        delete mainMenu[i];
    }
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
    sf::RenderTarget * temp;

    if (settings.doubleBuffered)
    {
        temp = &canvas;
        canvas.clear(sf::Color::Transparent);
    }
    else
    {
        temp = window;
    }

    temp->draw(background);
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        mainMenu[i]->draw(temp);
    }

    if (settings.doubleBuffered)
    {
        canvas.display();
        drawable.setPosition(0, 0);
        drawable.setTexture(canvas.getTexture());
        window->draw(drawable);
    }
}


int Menu::update(sf::Vector2i mousePos)
{
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        if(mainMenu[i]->update(mousePos))
        {
            switch(i)
            {
                case 0: //single player
                    return 1;
                    break;
                case 1: //multi player
                    return 2;
                    break;
                case 2: //options
                    break;
                case 3: //exit
                    return 10;
                    break;
            }
        }
    }

    return 0;
}

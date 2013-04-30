#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

const char * const Menu::keyNames[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Esc", "LCtrl", "LShift", "LAlt", "LOS", "RCtrl", "RShift", "RAlt", "ROS", "Menu", "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Space", "Return", "Backspace", "Tab", "PgUp", "PgDown", "End", "Home", "Insert", "Del", "Num+", "Num-", "Num*", "Num/", "Left", "Right", "Up", "Down", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

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

    //MAIN MENU
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

    //SETTINGS
    settingsMenu.push_back(new Button());   //back button
    settingsMenu[0]->initialize(100, 50);
    settingsMenu[0]->setPosition({50, 50});
    settingsMenu[0]->loadTexture("resources/back.png");
    settingsMenu[0]->setVisible(false);
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
    for(unsigned int i = 0; i < settingsMenu.size(); ++i)
    {
        settingsMenu[i]->draw(temp);
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
                    for (unsigned int a = 0; a < mainMenu.size(); ++a)
                    {
                        mainMenu[a]->setVisible(false);
                    }
                    for (unsigned int a = 0; a < settingsMenu.size(); ++a)
                    {
                        settingsMenu[a]->setVisible(true);
                    }
                    break;
                case 3: //exit
                    return 10;
                    break;
            }
        }
    }

    for(unsigned int i = 0; i < settingsMenu.size(); ++i)
    {
        if (settingsMenu[i]->update(mousePos))
        {
            switch(i)
            {
                case 0: //back
                    for (unsigned int a = 0; a < mainMenu.size(); ++a)
                    {
                        mainMenu[a]->setVisible(true);
                    }
                    for (unsigned int a = 0; a < settingsMenu.size(); ++a)
                    {
                        settingsMenu[a]->setVisible(false);
                    }
                    break;
                case 1:
                    break;
            }
        }
    }

    return 0;
}

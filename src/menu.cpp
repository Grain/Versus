#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Menu::Menu()
{
    if(!canvas.create(XRES, YRES))
        printf("Error in creating menu in state %i\n", menuState);

    initializeMenu();

    canvas.clear(sf::Color::Transparent);
    canvas.draw(menuSprite);
    canvas.display();
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

int Menu::getState()
{
    return menuState;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Menu::setState(int state)
{
    menuState = state;
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

/*******************PUBLIC FUNCTIONS****************************/
bool test;
void Menu::update(sf::Vector2i mousePos)
{
    if (!mousePos.x >= XRES - 131 && mousePos.x <= XRES - 65 && mousePos.y >= YRES - 120 && mousePos.y <= YRES - 90 && startBtnMO == true)
    {
        startBtn.setTexture(&startBtnTexture, true);
        startBtnMO = false;
        printf("redrawing menu\n");
        redrawMenu();
    }
    else if (mousePos.x >= XRES - 131 && mousePos.x <= XRES - 65 && mousePos.y >= YRES - 120 && mousePos.y <= YRES - 90 && startBtnMO == false)
    {
        startBtn.setTexture(&startBtnMOTexture, true);
        startBtnMO = true;
        printf("redrawing menu (MO)\n");
        redrawMenu();
    }
}

/*******************PRIVATE FUNCTIONS***************************/

void Menu::initializeMenu()
{
    setState(0); // main menu

    if (!menuTexture.create(XRES, YRES))
        printf("error initializing menu.\n");

    background.setFillColor(sf::Color::Black);
    background.setSize(sf::Vector2f(XRES, YRES));
    background.setPosition(0, 0);

    if (!startBtnTexture.loadFromFile("btnStart.png"))
        printf("error creating start button\n");
    startBtn.setTexture(&startBtnTexture);
    startBtn.setSize(sf::Vector2f(66, 30));
    startBtn.setPosition(XRES - 131, YRES - 120);

    if (!optionsBtnTexture.loadFromFile("btnOptions.png"))
        printf("error creating options button\n");
    optionsBtn.setTexture(&optionsBtnTexture);
    optionsBtn.setSize(sf::Vector2f(106, 30));
    optionsBtn.setPosition(XRES - 131, YRES - 85);

    if (!exitBtnTexture.loadFromFile("btnExit.png"))
        printf("error creating exit button\n");
    exitBtn.setTexture(&exitBtnTexture);
    exitBtn.setSize(sf::Vector2f(52, 30));
    exitBtn.setPosition(XRES - 131, YRES - 50);

    if (!startBtnMOTexture.loadFromFile("btnMOStart.png"))
        printf("error loading start button mouse over\n");

    redrawMenu();
}

void Menu::redrawMenu()
{
    menuTexture.clear(sf::Color::Transparent);
    menuTexture.draw(background);
    menuTexture.draw(startBtn);
    menuTexture.draw(optionsBtn);
    menuTexture.draw(exitBtn);
    menuTexture.display();
    menuSprite.setTexture(menuTexture.getTexture());
}

int Menu::checkClick(sf::Vector2i mousePos)
{
    if (!mousePos.x >= XRES - 131 && mousePos.x <= XRES - 65 && mousePos.y >= YRES - 120 && mousePos.y <= YRES - 90)
    {
        return -1;
    }
    else if (mousePos.x >= XRES - 131 && mousePos.x <= XRES - 65 && mousePos.y >= YRES - 120 && mousePos.y <= YRES - 90)
    {
        return 1;
    }
}

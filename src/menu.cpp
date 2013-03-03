#include "menu.h"


/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Menu::Menu()
{
    size = {xRes, yRes};
    position = {0, 0};

    if(!canvas.create(size.x, size.y))
        printf("Error in main menu\n");    //maybe identification of tower?

    static sf::RenderTexture grid;

    mainMenu = initializeMenu();
    mainMenu.setPosition(0, 0);
    mainBtns = initializeBtns();

    canvas.clear(sf::Color::Transparent);
    canvas.draw(mainMenu);
    canvas.draw(mainBtns);
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

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

sf::Sprite Menu::initializeMenu()
{
    static sf::RenderTexture grid;

    if(!grid.create(xRes,yRes))
        printf("error in initializeGrid\n");
    grid.clear(sf::Color::Transparent);

    sf::RectangleShape temp;

    temp.setFillColor(sf::Color::Black);
    temp.setSize(sf::Vector2f(xRes, yRes));
    temp.setPosition(0, 0);

    grid.draw(temp);
    grid.display();
    return sf::Sprite(grid.getTexture());  //memory leak?
}

sf::Sprite Menu::initializeBtns()
{
    static sf::RenderTexture grid;

    if(!grid.create(xRes,yRes))
        printf("error in initializeBtns\n");
    grid.clear(sf::Color::Transparent);

/*******************BUTTONS*************************************/

    sf::Texture startBtnTexture, optionsBtnTexture, exitBtnTexture;
    sf::RectangleShape startBtn, optionsBtn, exitBtn;

    if (!startBtnTexture.loadFromFile("btnStart.png"))
        printf("error creating start button\n");
    startBtn.setTexture(&startBtnTexture);
    startBtn.setSize(sf::Vector2f(66, 30));
    startBtn.setPosition(xRes - 131, yRes - 120);
    grid.draw(startBtn);

    if (!optionsBtnTexture.loadFromFile("btnOptions.png"))
        printf("error creating options button\n");
    optionsBtn.setTexture(&optionsBtnTexture);
    optionsBtn.setSize(sf::Vector2f(106, 30));
    optionsBtn.setPosition(xRes - 131, yRes - 85);
    grid.draw(optionsBtn);

    if (!exitBtnTexture.loadFromFile("btnExit.png"))
        printf("error creating exit button\n");
    exitBtn.setTexture(&exitBtnTexture);
    exitBtn.setSize(sf::Vector2f(52, 30));
    exitBtn.setPosition(xRes - 131, yRes - 50);
    grid.draw(exitBtn);

/***************************************************************/

    grid.display();
    return sf::Sprite(grid.getTexture());  //memory leak?
}

void Menu::update(sf::Vector2i mousePos)
{

}

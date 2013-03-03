#include "btn.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Btn::Btn()
{
    size = {xRes, yRes};

    if(!canvas.create(size.x, size.y))
        printf("Error in creating tower\n");    //maybe output identification of tower?

    exitBtn = initializeBtns(0);
    exitBtn.setPosition(sf::Vector2f(xRes - 75, yRes - 55));

/*  This works to spawn the rectangle

    sf::Texture tempTexture;
    sf::RectangleShape temp;

    if (!tempTexture.loadFromFile("btnExit.png"))
        printf("error creating exit button\n");

    temp.setTexture(&tempTexture);
    temp.setSize(sf::Vector2f(50, 30));
    temp.setPosition(xRes - 75, yRes - 55);

*/
    //startBtn = initializeBtns(1);
    //optionBtn = initializeBtns(2);
    // set the position of the buttons

    canvas.clear(sf::Color::Transparent);

    canvas.draw(exitBtn); // draw the buttons
    //canvas.draw(startBtn);
    //canvas.draw(optionBtn);
    printf("buttons rendered.");
    canvas.display();
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Btn::~Btn()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

sf::Vector2i Btn::getCoordinates()
{
    return coordinates;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

void Btn::setCoordinates(sf::Vector2i i)
{
    coordinates = i;
    position = {(float) i.x, (float) i.y};
}

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

sf::Sprite Btn::initializeBtns(int code)
{
    static sf::RenderTexture grid;

    if(!grid.create(xRes,yRes))
        printf("error in initializeBtns\n");
    grid.clear(sf::Color::Transparent);

    sf::Texture tempTexture;
    sf::RectangleShape temp;
    switch (code)
    {
        case 0:
            if (!tempTexture.loadFromFile("btnExit.png"))
                printf("error creating exit button\n");
            break;
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }
    temp.setTexture(&tempTexture);
    temp.setSize(sf::Vector2f(50, 30));
    temp.setPosition(xRes - 75, yRes - 55);

    grid.draw(temp);
    grid.display();
    return sf::Sprite(grid.getTexture());  //memory leak?
}

void Btn::update()
{
    canvas.clear(sf::Color::Transparent);

    canvas.display();
}

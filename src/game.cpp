#include "game.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Game::Game()
{
    size = {xRes, yRes};
    position = {0, 0};

    if(!canvas.create(size.x, size.y))
        printf("Error in creating Game\n");

    field = initializeGrid(sf::Color::Yellow, sf::Color::Green);    //temp colours
    field.setPosition(40, 0);

    tower.setCoordinates({15, 5});

    canvas.clear(sf::Color::Transparent);
    canvas.draw(field);
    canvas.draw(tower.getSprite());
    canvas.display();
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Game::~Game()
{

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

void Game::update(sf::Vector2i mousePos)
{
    tower.setRotation(mousePos.x); //temp
    tower.update();

    canvas.clear(sf::Color::Transparent);
    canvas.draw(field);
    canvas.draw(tower.getSprite());
    canvas.display();
}

sf::Sprite Game::initializeGrid(sf::Color left, sf::Color right)
{
    const int boxDimensions = 40;   //each box in the grid is 40x40, not including the lines
    const int gridDimensions = 10;  //grid is 10x10 on each side
    const int middle = 3;  //3 box wide in the middle

    static sf::RenderTexture grid;

    if(!grid.create(boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, boxDimensions * gridDimensions + gridDimensions + 1))
        printf("error in initializeGrid\n");
    grid.clear(sf::Color::Transparent);

    sf::RectangleShape temp(sf::Vector2f(944, 411));

    //left side background colour
    temp.setFillColor(left);
    temp.setSize(sf::Vector2f(boxDimensions * gridDimensions + gridDimensions + 1, boxDimensions * gridDimensions + gridDimensions + 1));
    temp.setPosition(0, 0);
    grid.draw(temp);

    //right side background colour
    temp.setFillColor(right);
    temp.setSize(sf::Vector2f(boxDimensions * gridDimensions + gridDimensions + 1,boxDimensions * gridDimensions + gridDimensions + 1));
    temp.setPosition((gridDimensions + middle) * boxDimensions + gridDimensions + middle + 1, 0);
    grid.draw(temp);

    //vertical lines
    int i;
    for(i = 0; i <= 2 * gridDimensions + middle; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize(sf::Vector2f(1, boxDimensions * gridDimensions + gridDimensions + 1));
        temp.setPosition(i * (boxDimensions + 1), 0);
        grid.draw(temp);
    }
    //horizontal lines
    for(i = 0; i <= gridDimensions; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize(sf::Vector2f(boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, 1));
        temp.setPosition(0, i * (boxDimensions + 1));
        grid.draw(temp);
    }

    grid.display();
    return sf::Sprite(grid.getTexture());  //memory leak?
}

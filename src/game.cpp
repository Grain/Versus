#include "game.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Game::Game()
{
    if(!canvas.create(xRes, yRes))
        printf("Error in creating Game\n");

    initializeGrid(sf::Color::Yellow, sf::Color::Green);    //temp colours
    gridSprite.setPosition(40, 0);

    towerTexture.create(40, 40);

    canvas.clear(sf::Color::Transparent);
    canvas.draw(gridSprite);
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
    printf("%d\n", towers.size());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        towers.push_back(new Tower(&towerTexture, &towerSprite));
        towers[towers.size() - 1]->setCoordinates(gridPosition(mousePos));
    }
    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        towers[i]->setRotation(mousePos.x);
    }

    canvas.clear(sf::Color::Transparent);
    canvas.draw(gridSprite);
    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        towers[i]->draw(&canvas);
    }
    canvas.display();
}

void Game::initializeGrid(sf::Color left, sf::Color right)
{
    const int boxDimensions = 40;   //each box in the grid is 40x40, not including the lines
    const int gridDimensions = 10;  //grid is 10x10 on each side
    const int middle = 3;  //3 box wide in the middle

    if(!gridTexture.create(boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, boxDimensions * gridDimensions + gridDimensions + 1))
        printf("error in initializeGrid\n");
    gridTexture.clear(sf::Color::Transparent);

    sf::RectangleShape temp;

    //left side background colour
    temp.setFillColor(left);
    temp.setSize({boxDimensions * gridDimensions + gridDimensions + 1, boxDimensions * gridDimensions + gridDimensions + 1});
    temp.setPosition(0, 0);
    gridTexture.draw(temp);

    //right side background colour
    temp.setFillColor(right);
    temp.setSize({boxDimensions * gridDimensions + gridDimensions + 1,boxDimensions * gridDimensions + gridDimensions + 1});
    temp.setPosition((gridDimensions + middle) * boxDimensions + gridDimensions + middle + 1, 0);
    gridTexture.draw(temp);

    //vertical lines
    int i;
    for(i = 0; i <= 2 * gridDimensions + middle; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({1, boxDimensions * gridDimensions + gridDimensions + 1});
        temp.setPosition(i * (boxDimensions + 1), 0);
        gridTexture.draw(temp);
    }
    //horizontal lines
    for(i = 0; i <= gridDimensions; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, 1});
        temp.setPosition(0, i * (boxDimensions + 1));
        gridTexture.draw(temp);
    }

    gridTexture.display();
    gridSprite.setTexture(gridTexture.getTexture());
}

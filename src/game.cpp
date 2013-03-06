#include "game.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Game::Game()
{
    if(!canvas.create(XRES, YRES))
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
    if(!gridTexture.create(BOXDIMENSIONS * (2 * GRIDX + MIDDLE) + GRIDX * 2 + MIDDLE + 1, BOXDIMENSIONS * GRIDY + GRIDY + 1))
        printf("error in initializeGrid\n");
    gridTexture.clear(sf::Color::Transparent);

    sf::RectangleShape temp;

    //left side background colour
    temp.setFillColor(left);
    temp.setSize({BOXDIMENSIONS * GRIDX + GRIDX + 1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
    temp.setPosition(0, 0);
    gridTexture.draw(temp);

    //right side background colour
    temp.setFillColor(right);
    temp.setSize({BOXDIMENSIONS * GRIDX + GRIDX + 1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
    temp.setPosition((GRIDX + MIDDLE) * BOXDIMENSIONS + GRIDY + MIDDLE + 1, 0);
    gridTexture.draw(temp);

    //vertical lines
    int i;
    for(i = 0; i <= 2 * GRIDX + MIDDLE; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
        temp.setPosition(i * (BOXDIMENSIONS + 1), 0);
        gridTexture.draw(temp);
    }
    //horizontal lines
    for(i = 0; i <= GRIDY; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({BOXDIMENSIONS * (2 * GRIDX + MIDDLE) + GRIDX * 2 + MIDDLE + 1, 1});
        temp.setPosition(0, i * (BOXDIMENSIONS + 1));
        gridTexture.draw(temp);
    }

    gridTexture.display();
    gridSprite.setTexture(gridTexture.getTexture());
}

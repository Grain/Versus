#include "game.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Game::Game()
{
    for(int a = 0; a < GRIDX * 2 + MIDDLE; ++a)
    {
        for(int b = 0; b < GRIDY; ++b)
        {
            map[a][b] = false;
        }
    }

    if (settings.doubleBuffered)
    {
        if(!canvas.create(XRES, YRES))
            printf("Error creating game renderTexture\n");
    }
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

void Game::draw(sf::RenderWindow * window)
{
    if (settings.doubleBuffered)
    {
        canvas.clear(sf::Color::Transparent);

        initializeGrid(&canvas, sf::Color::Yellow, sf::Color::Green);    //temp colours
        for(unsigned int i = 0; i < towers.size(); ++i)
        {
            towers[i]->draw(&canvas);
        }
        canvas.display();
        drawable.setTexture(canvas.getTexture());
        window->draw(drawable);
    }
    else
    {
        initializeGrid(window, sf::Color::Yellow, sf::Color::Green);    //temp colours
        for(unsigned int i = 0; i < towers.size(); ++i)
        {
            towers[i]->draw(window);
        }
    }
}

void Game::update(sf::Vector2i mousePos)
{
    printf("%d\n", towers.size());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        newTower(gridPosition(mousePos));
    }

    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        towers[i]->setRotation(mousePos.x);
    }
}

void Game::newTower(sf::Vector2i i)
{
    if (i.x >= 0 && i.x < GRIDX * 2 + MIDDLE && i.y >= 0 && i.y < GRIDY)
    {
        if (map[i.x][i.y] == false)
        {
            map[i.x][i.y] = true;
            towers.push_back(new Tower());
            towers[towers.size() - 1]->setCoordinates(i);
        }
    }
}

void Game::initializeGrid(sf::RenderTarget* target, sf::Color left, sf::Color right)
{
    sf::RectangleShape temp;
    const int offset = (XRES - (BOXDIMENSIONS * (2 * GRIDX + MIDDLE) + GRIDX * 2 + MIDDLE + 1)) / 2;

    //left side background colour
    temp.setFillColor(left);
    temp.setSize({BOXDIMENSIONS * GRIDX + GRIDX + 1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
    temp.setPosition(offset, 0);
    target->draw(temp);

    //right side background colour
    temp.setFillColor(right);
    temp.setSize({BOXDIMENSIONS * GRIDX + GRIDX + 1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
    temp.setPosition((GRIDX + MIDDLE) * BOXDIMENSIONS + GRIDY + MIDDLE + 1 + offset, 0);
    target->draw(temp);

    //vertical lines
    int i;
    for(i = 0; i <= 2 * GRIDX + MIDDLE; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({1, BOXDIMENSIONS * GRIDY + GRIDY + 1});
        temp.setPosition(i * (BOXDIMENSIONS + 1) + offset, 0);
        target->draw(temp);
    }
    //horizontal lines
    for(i = 0; i <= GRIDY; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize({BOXDIMENSIONS * (2 * GRIDX + MIDDLE) + GRIDX * 2 + MIDDLE + 1, 1});
        temp.setPosition(offset, i * (BOXDIMENSIONS + 1));
        target->draw(temp);
    }
}

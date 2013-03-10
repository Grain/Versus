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
            calculateDistances();
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
    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        delete towers[i];
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
    //printf("%d\n", towers.size());

//    for(int a = 0; a < GRIDY; ++a)
//    {
//        for(int b = 0; b < GRIDX * 2 + MIDDLE; ++b)
//        {
//            printf("%d\t", distancesLeft[a][b]);
//        }
//        printf("\n");
//    }

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
    //does not allow creating tower outside of grid OR creating tower on spawn points
    if (i.x >= 0 && i.x < GRIDX * 2 + MIDDLE && i.y >= 0 && i.y < GRIDY && !(i.x == 0 && i.y == GRIDY / 2) && !(i.x == GRIDX * 2 + MIDDLE - 1 && i.y == GRIDY / 2))
    {
        if (map[i.x][i.y] == false)
        {
            map[i.x][i.y] = true;
            calculateDistances();
            towers.push_back(new Tower());
            towers[towers.size() - 1]->setCoordinates(i);
        }
    }

    //print current distances
    printf("\n");
    printf("\n");

    for(int a = 0; a < GRIDY; ++a)
    {
        for(int b = 0; b < GRIDX * 2 + MIDDLE; ++b)
        {
            if(distancesRight[b][a] == 99999)
            {
                printf("*  ");
                continue;
            }
            printf("%d ", distancesRight[b][a]);
            if (distancesRight[b][a] < 10)
                printf(" ");
        }
        printf("\n");
    }
}

void Game::calculateDistances()
{
    const int EMPTY = 9999;

    for(int a = 0; a < GRIDX * 2 + MIDDLE; ++a)
    {
        for(int b = 0; b < GRIDY; ++b)
        {
            if(map[a][b] == true)
            {
                distancesLeft[a][b] = 99999;   //tower on that part
                distancesRight[a][b] = 99999;
            }
            else
            {
                distancesLeft[a][b] = EMPTY;
                distancesRight[a][b] = EMPTY;
            }
        }
    }

    distancesLeft[0][GRIDY / 2] = 1;
    distancesRight[GRIDX * 2 + MIDDLE - 1][GRIDY / 2] = 1;

    int choices[] = {0, 0, 0, 0};
    int a, b;
    std::queue<sf::Vector2i> next;

    //left side

    if(distancesLeft[1][GRIDY / 2] == EMPTY)        //push to queue initial coordinates
        next.push({1, GRIDY / 2});
    if(distancesLeft[0][GRIDY / 2 + 1] == EMPTY)
        next.push({0, GRIDY / 2 + 1});
    if(distancesLeft[0][GRIDY / 2 - 1] == EMPTY)
        next.push({0, GRIDY / 2 - 1});

    while (next.empty() == false)
    {   //yay hardcode
        a = next.front().x;
        b = next.front().y;
        next.pop();

        choices[0] = choices[1] = choices[2] = choices[3] = EMPTY;

        if(distancesLeft[a][b] == EMPTY)
        {
            if(a > 0)
            {
                choices[0] = distancesLeft[a - 1][b];
                if (choices[0] == EMPTY)
                {
                    next.push({a - 1, b});
                }
            }
            if(a < GRIDX * 2 + MIDDLE - 1)
            {
                choices[1] = distancesLeft[a + 1][b];
                if (choices[1] == EMPTY)
                {
                    next.push({a + 1, b});
                }
            }
            if(b > 0)
            {
                choices[2] = distancesLeft[a][b - 1];
                if (choices[2] == EMPTY)
                {
                    next.push({a, b - 1});
                }
            }
            if(b < GRIDY - 1)
            {
                choices[3] = distancesLeft[a][b + 1];
                if (choices[3] == EMPTY)
                {
                    next.push({a, b + 1});
                }
            }

            int smallest = choices[0];
            for(int i = 1; i < 4; ++i)
            {
                if(choices[i] < smallest)
                {
                    smallest = choices[i];
                }
            }

            distancesLeft[a][b] = smallest + 1;
        }
    }

    //right side
    if(distancesRight[GRIDX * 2 + MIDDLE - 2][GRIDY / 2] == EMPTY)        //push to queue initial coordinates
        next.push({GRIDX * 2 + MIDDLE - 2, GRIDY / 2});
    if(distancesRight[GRIDX * 2 + MIDDLE - 1][GRIDY / 2 + 1] == EMPTY)
        next.push({GRIDX * 2 + MIDDLE - 1, GRIDY / 2 + 1});
    if(distancesRight[GRIDX * 2 + MIDDLE - 1][GRIDY / 2 - 1] == EMPTY)
        next.push({GRIDX * 2 + MIDDLE - 1, GRIDY / 2 - 1});

    while (next.empty() == false)
    {   //yay hardcode
        a = next.front().x;
        b = next.front().y;
        next.pop();

        choices[0] = choices[1] = choices[2] = choices[3] = EMPTY;

        if(distancesRight[a][b] == EMPTY)
        {
            if(a > 0)
            {
                choices[0] = distancesRight[a - 1][b];
                if (choices[0] == EMPTY)
                {
                    next.push({a - 1, b});
                }
            }
            if(a < GRIDX * 2 + MIDDLE - 1)
            {
                choices[1] = distancesRight[a + 1][b];
                if (choices[1] == EMPTY)
                {
                    next.push({a + 1, b});
                }
            }
            if(b > 0)
            {
                choices[2] = distancesRight[a][b - 1];
                if (choices[2] == EMPTY)
                {
                    next.push({a, b - 1});
                }
            }
            if(b < GRIDY - 1)
            {
                choices[3] = distancesRight[a][b + 1];
                if (choices[3] == EMPTY)
                {
                    next.push({a, b + 1});
                }
            }

            int smallest = choices[0];
            for(int i = 1; i < 4; ++i)
            {
                if(choices[i] < smallest)
                {
                    smallest = choices[i];
                }
            }

            distancesRight[a][b] = smallest + 1;
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

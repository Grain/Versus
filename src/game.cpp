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

    calculateDistances();

    if (settings.doubleBuffered)
    {
        if(!canvas.create(XRES, YRES))
            printf("Error creating game renderTexture\n");
    }

    players = left;
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

void Game::newGame()
{
    sf::Image temp;
    temp.loadFromFile("resources/selector.png");
    selectorTextures[0].loadFromImage(temp);
    temp.flipVertically();
    selectorTextures[1].loadFromImage(temp);

    for(int i = 0; i < 2; ++i)
    {
        selector[i].setSize({BOXDIMENSIONS, BOXDIMENSIONS});
        selector[i].setTexture(&selectorTextures[i]);
    }

    selector[0].setFillColor(sf::Color::Cyan);
    selectorCoordinates[0] = {0, GRIDY / 2};

    selector[1].setFillColor(sf::Color::Magenta);
    selectorCoordinates[1] = {GRIDX * 2 + MIDDLE - 1, GRIDY / 2};

    prevMouse = {0, 0};

    prevKeys[0] = prevKeys[1] = {false, false, false, false, false, false};
}

void Game::draw(sf::RenderWindow * window)
{
    int begin, end;

    if(players == left || players == both)
        begin = 0;
    else
        begin = 1;
    if(players == right || players == both)
        end = 2;
    else
        end = 1;

    if (settings.doubleBuffered)
    {
        canvas.clear(sf::Color::Transparent);

        initializeGrid(&canvas, sf::Color::Yellow, sf::Color::Green);    //temp colours
        for(unsigned int i = 0; i < towers.size(); ++i)
        {
            towers[i]->draw(&canvas);
        }
        for(int i = begin; i < end; ++i)
        {
            canvas.draw(selector[i]);
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

        for(int i = begin; i < end; ++i)
        {
            window->draw(selector[i]);
        }
    }
}

int Game::update(sf::Vector2i mousePos)
{
    static const int gridSize = BOXDIMENSIONS + 1; //grid box + border

    if (mousePos != prevMouse && settings.enableMouse == true)
    {
        if (players == left)
        {
            sf::Vector2i tempCoordinate = gridPosition(mousePos);
            if(!(tempCoordinate.x < 0 || tempCoordinate.x >= GRIDX * 2 + MIDDLE || tempCoordinate.y < 0 || tempCoordinate.y >= GRIDY))
            {
                selectorCoordinates[0] = tempCoordinate;
            }
        }
        else if (players == right)
        {
            sf::Vector2i tempCoordinate = gridPosition(mousePos);
            if(!(tempCoordinate.x < 0 || tempCoordinate.x >= GRIDX * 2 + MIDDLE || tempCoordinate.y < 0 || tempCoordinate.y >= GRIDY))
            {
                selectorCoordinates[1] = tempCoordinate;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(players == left)
            {
                newTower(selectorCoordinates[0]);
            }
            if(players == right)
            {
                newTower(selectorCoordinates[1]);
            }
        }
    }
    prevMouse = mousePos;

    int begin, end;

    if(players == left || players == both)
        begin = 0;
    else
        begin = 1;
    if(players == right || players == both)
        end = 2;
    else
        end = 1;

    for(int i = begin; i < end; ++i)
    {
        Keys temp;
        if(i == 0)
            temp = settings.leftPlayer;
        else
            temp = settings.rightPlayer;

        if(sf::Keyboard::isKeyPressed(temp.up))
        {
            if(prevKeys[i].up == false)
                selectorCoordinates[i].y -= 1;
            prevKeys[i].up = true;
        }
        else
        {
            prevKeys[i].up = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.down))
        {
            if(prevKeys[i].down == false)
                selectorCoordinates[i].y += 1;
            prevKeys[i].down = true;
        }
        else
        {
            prevKeys[i].down = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.left))
        {
            if(prevKeys[i].left == false)
                selectorCoordinates[i].x -= 1;
            prevKeys[i].left = true;
        }
        else
        {
            prevKeys[i].left = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.right))
        {
            if(prevKeys[i].right == false)
                selectorCoordinates[i].x += 1;
            prevKeys[i].right = true;
        }
        else
        {
            prevKeys[i].right = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.select))
        {
            if(prevKeys[i].select == false)
            {
                newTower(selectorCoordinates[i]);
            }
            prevKeys[i].select = true;
        }
        else
        {
            prevKeys[i].select = false;
        }

        if (selectorCoordinates[i].y < 0)
            selectorCoordinates[i].y = GRIDY - 1;
        if (selectorCoordinates[i].y > GRIDY - 1)
            selectorCoordinates[i].y = 0;
        if (selectorCoordinates[i].x < 0)
            selectorCoordinates[i].x = GRIDX * 2 + MIDDLE - 1;
        if (selectorCoordinates[i].x > GRIDX * 2 + MIDDLE - 1)
            selectorCoordinates[i].x = 0;
    }

    for(int i = 0; i < 2; ++i)
    {
        selector[i].setPosition((float)(gridSize + selectorCoordinates[i].x * gridSize), (float)(1 + selectorCoordinates[i].y * gridSize));
    }

    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        towers[i]->setRotationTarget((sf::Vector2f)mousePos);
//        towers[i]->setRotation(mousePos.x);
    }

    return 0;
}

void Game::newTower(sf::Vector2i i)
{
    //not allowing placing towers in middle should be in the gui

    //does not allow creating tower outside of grid
    if (i.x >= 0 && i.x < GRIDX * 2 + MIDDLE && i.y >= 0 && i.y < GRIDY)
    {
        if ((i.x == 0 && i.y == GRIDY / 2) || (i.x == GRIDX * 2 + MIDDLE - 1 && i.y == GRIDY / 2))   //trying to place tower on spawn points
        {

        }
        else if(i.x >= GRIDX && i.x < GRIDX + MIDDLE)
        {

        }
        else
        {
            //todo: check for creeps on spot
            if (map[i.x][i.y] == false) //if the spot is empty
            {
                map[i.x][i.y] = true;
                calculateDistances();
                if (distancesRight[0][GRIDY / 2] == EMPTY)
                {
                    //no path available
                    map[i.x][i.y] = false;
                    calculateDistances();   //should i use distances for pathfinding, or actual paths??
                }
                else
                {
                    towers.push_back(new Tower());
                    towers[towers.size() - 1]->setCoordinates(i);
                }
            }
        }
    }

//    //print current distances
//    printf("\n");
//    printf("\n");
//
//    for(int a = 0; a < GRIDY; ++a)
//    {
//        for(int b = 0; b < GRIDX * 2 + MIDDLE; ++b)
//        {
//            if(distancesRight[b][a] == FILLED)
//            {
//                printf("*  ");
//                continue;
//            }
//            printf("%d ", distancesRight[b][a]);
//            if (distancesRight[b][a] < 10)
//                printf(" ");
//        }
//        printf("\n");
//    }
}

void Game::calculateDistances()
{

    for(int a = 0; a < GRIDX * 2 + MIDDLE; ++a)
    {
        for(int b = 0; b < GRIDY; ++b)
        {
            if(map[a][b] == true)
            {
                distancesLeft[a][b] = FILLED;   //tower on that part
                distancesRight[a][b] = FILLED;
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

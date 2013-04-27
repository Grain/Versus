#include "game.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Game::Game()
{
    sf::Image temp;
    temp.loadFromFile("resources/selector.png");
    selectorTextures[0].loadFromImage(temp);
    temp.flipVertically();
    selectorTextures[1].loadFromImage(temp);

    backgroundTexture.loadFromFile("resources/gameBackground.png");
    background.setSize({XRES, YRES});
    background.setPosition(0, 0);
    background.setTexture(&backgroundTexture);

    timer.setColor(sf::Color(128, 128, 128));
    timer.setCharacterSize(26);
    timer.setStyle(sf::Text::Bold);
    timer.setString("0:30");
    timer.setOrigin(timer.getGlobalBounds().width / 2, timer.getGlobalBounds().height / 2);
    timer.setPosition(XRES / 2, 406);
    timerBackground.setSize({80, 34});
    timerBackground.setOrigin(timerBackground.getSize().x / 2, timerBackground.getSize().y / 2);
    timerBackground.setPosition(timer.getGlobalBounds().left + timer.getGlobalBounds().width / 2, timer.getGlobalBounds().top + timer.getGlobalBounds().height / 2);
    timerBackground.setFillColor(sf::Color::Transparent);
    timerBackground.setOutlineColor(sf::Color::Black);
    timerBackground.setOutlineThickness(2);
    timerBar.setSize({0, 34});
    timerBar.setPosition(timerBackground.getGlobalBounds().left + timerBackground.getOutlineThickness(), timerBackground.getGlobalBounds().top + timerBackground.getOutlineThickness());
    timerBar.setFillColor(sf::Color::Green);

    speedBackgroundTexture.loadFromFile("resources/speed.png");
    speedBackground.setSize({80, 40});
    speedBackground.setOrigin(speedBackground.getSize().x / 2, timerBackground.getSize().y / 2);
    speedBackground.setPosition(XRES / 2, 470);
    speedBackground.setTexture(&speedBackgroundTexture, true);
    speedBackground.setTextureRect(sf::IntRect(0, 0, speedBackground.getSize().x, speedBackground.getSize().y));
    speedBackground.setFillColor(sf::Color::Blue);
    speedBackground.setOutlineColor(sf::Color::Black);
    speedBackground.setOutlineThickness(2);
    fastForwardTexture.loadFromFile("resources/fastForward.png");
    fastForward.setSize(speedBackground.getSize());
    fastForward.setPosition(speedBackground.getGlobalBounds().left + 2, speedBackground.getGlobalBounds().top + 2);
    fastForward.setTexture(&fastForwardTexture);

    pause.initialize(84, 40);
    pause.setPosition({XRES / 2 - pause.getSize().x / 2, 516});
    pause.loadTexture("resources/pause.png");
    resume.initialize(100, 50);
    resume.setPosition({XRES / 2 - resume.getSize().x / 2, 200});
    resume.loadTexture("resources/resume.png");
    resume.setVisible(false);
    exit.initialize(100, 50);
    exit.setPosition({XRES / 2 - exit.getSize().x / 2, 300});
    exit.loadTexture("resources/exit.png");
    exit.setVisible(false);
    pauseBackground.setSize({XRES, YRES});
    pauseBackground.setPosition({0, 0});
    pauseBackground.setFillColor(sf::Color(0, 0, 0, 128));

    for (int i = 0; i < 2; ++i)
    {
        ranges[i].setFillColor(sf::Color::Transparent);
        ranges[i].setOutlineColor(sf::Color::Black);
        ranges[i].setOutlineThickness(1);
        ranges[i].setPointCount(50);
        visibleRanges[i] = false;
    }

    for(int i = 0; i < 2; ++i)
    {
        selector[i].setSize({BOXDIMENSIONS, BOXDIMENSIONS});
        selector[i].setTexture(&selectorTextures[i]);

        buttonSelector[i].setTexture(&selectorTextures[i]);

        for(int a = 0; a < 4; ++a)
        {
            int offset = 180;
            int spacing = 5;
            if (i == 1)
            {
                offset = XRES - (offset + 3 * (60 + spacing) + 60);
            }
            gameButtons[i][a].initialize(60, 40);
            gameButtons[i][a].setPosition({(float)(offset + a * (gameButtons[i][a].getSize().x + spacing)) , 390});
            gameButtons[i][a].loadTexture("resources/something.png");
            gameButtons[i][a].setVisible(true);
        }

        for(int a = 0; a < 4; ++a)
        {
            int offset = 180;
            int spacing = 5;
            if (i == 1)
            {
                offset = XRES - (offset + 3 * (60 + spacing) + 60);
            }
            gameButtons[i][4 + a].initialize(60, 60);
            gameButtons[i][4 + a].setPosition({(float)(offset + a * (gameButtons[i][4 + a].getSize().x + spacing)), 440});
            gameButtons[i][4 + a].loadTexture("resources/something.png");
            gameButtons[i][4 + a].setVisible(true); //false
        }

        for(int a = 0; a < 3; ++a)
        {
            int offset = 200;
            int spacing = 15;
            if (i == 1)
            {
                offset = XRES - (offset + 2 * (40 + spacing) + 40);
            }
            gameButtons[i][8 + a].initialize(40, 40);
            gameButtons[i][8 + a].setPosition({(float)(offset + a * (gameButtons[i][8 + a].getSize().x + spacing)), 510});
            gameButtons[i][8 + a].loadTexture("resources/something.png");
            gameButtons[i][8 + a].setVisible(true);
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

    for (int a = 0; a < 2; ++a)
    {
        for (unsigned int b = 0; b < creeps[a].size(); ++b)
        {
            delete creeps[a][b];
        }
    }

    for (unsigned int i = 0; i < projectiles.size(); ++i)
    {
        delete projectiles[i];
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

void Game::newGame(Game::Players temp)
{
    players = temp;

    selector[0].setFillColor(sf::Color::Cyan);  //temp
    buttonSelector[0].setFillColor(sf::Color::Cyan);  //temp
    selectorCoordinates[0] = {0, GRIDY / 2};

    selector[1].setFillColor(sf::Color::Magenta);   //temp
    buttonSelector[1].setFillColor(sf::Color::Magenta);   //temp
    selectorCoordinates[1] = {GRIDX * 2 + MIDDLE - 1, GRIDY / 2};
    selected[0] = selected[1] = false;
    inGrid[0] = inGrid[1] = false;

    ranges[0].setOutlineColor(sf::Color::Cyan); //temp
    ranges[1].setOutlineColor(sf::Color::Magenta); //temp
    visibleRanges[0] = false;
    visibleRanges[1] = false;

    buttonSelector[0].setSize(gameButtons[0][4].getSize());
    buttonSelector[1].setSize(gameButtons[1][4].getSize());
    buttonSelector[0].setPosition(gameButtons[0][4].getPosition());
    buttonSelector[1].setPosition(gameButtons[1][4].getPosition());

    middleCoordinates[0] = middleCoordinates[1] = 0;

    prevMouse = {0, 0};

    prevKeys[0] = prevKeys[1] = {false, false, false, false, false, false};

    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        delete towers[i];
    }
    towers.clear();

    for (int a = 0; a < 2; ++a)
    {
        for (unsigned int b = 0; b < creeps[a].size(); ++b)
        {
            delete creeps[a][b];
        }
        creeps[a].clear();
    }

    for (unsigned int i = 0; i < projectiles.size(); ++i)
    {
        delete projectiles[i];
    }
    projectiles.clear();

    for(int a = 0; a < GRIDX * 2 + MIDDLE; ++a)
    {
        for(int b = 0; b < GRIDY; ++b)
        {
            map[a][b] = false;
        }
    }

    calculateDistances();

    time = -30;

    speedUp = false;
    speedUpAnimation = 0;

    paused = false;
    prevEscape = false;
    resume.setVisible(false);
    exit.setVisible(false);
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
    initializeGrid(temp, sf::Color(255, 255, 0, 128), sf::Color(0, 255, 0, 128));     //temp colours

    for(unsigned int i = 0; i < towers.size(); ++i)
    {
        towers[i]->draw(temp);
    }

    for(int b = 0; b < 2; ++b)
    {
        for(unsigned int i = 0; i < creeps[b].size(); ++i)
        {
            creeps[b][i]->draw(temp);
        }
    }

    for (unsigned int i = 0; i < projectiles.size(); ++i)
    {
        projectiles[i]->draw(temp);
    }

    for (int i = 0; i < 2; ++i)
    {
        if (visibleRanges[i])
        {
            temp->draw(ranges[i]);
        }
    }

    for(int i = begin; i < end; ++i)
    {
        temp->draw(selector[i]);

        for(int a = 0; a < 11; ++a)
        {
            gameButtons[i][a].draw(temp);
        }

        if (selected[i])
        {
            temp->draw(buttonSelector[i]);
        }
    }
    temp->draw(timerBackground);
    temp->draw(timerBar);
    temp->draw(timer);
    temp->draw(speedBackground);
    temp->draw(fastForward);

    pause.draw(temp);

    if(paused)
    {
        temp->draw(pauseBackground);
        resume.draw(temp);
        exit.draw(temp);
    }

    if (settings.doubleBuffered)
    {
        canvas.display();
        drawable.setTexture(canvas.getTexture());
        window->draw(drawable);
    }
}

int Game::update(sf::Vector2i mousePos)
{
    if (paused)
    {
        if (resume.update(mousePos))
        {
            resume.setVisible(!paused);
            exit.setVisible(!paused);
            paused = !paused;
        }
        if (exit.update(mousePos))
        {
            return 1;
        }
    }
    else
    {
        if (pause.update(mousePos))
        {
            resume.setVisible(!paused);
            exit.setVisible(!paused);
            paused = !paused;
            return 0;
        }

        mouseSelector(mousePos);
        keyboardSelector(mousePos);

        //game buttons
        for(int i = 0; i < 2; ++i)
        {
            buttonSelector[i].setSize(gameButtons[i][4 + middleCoordinates[i]].getSize());
            buttonSelector[i].setPosition(gameButtons[i][4 + middleCoordinates[i]].getPosition());

            for(int a = 0; a < 11; ++a)
            {
                if (gameButtons[i][a].update(mousePos))
                {
                    if (settings.enableMouse == true && players != both)
                    {
                        if (a >= 4 && a <= 7)   //is middle row button
                        {
                            if (selected[i])
                            {
                                printf("button %d pressed\n", a - 4);
                            }
                        }
                        else
                        {
                            printf("button asdf pressed %d\n", a);
                        }
                    }
                }
            }
        }

        ////////////////////////////////

        for(int i = 0; i < 2; ++i)
        {
            selector[i].setPosition((sf::Vector2f)coordinatePosition(selectorCoordinates[i]));

            int showRange = false;
            for (unsigned int a = 0; a < towers.size(); ++a)
            {
                if (selectorCoordinates[i] == towers[a]->getCoordinates())
                {
                    showRange = true;
                    ranges[i].setRadius(towers[a]->getRange());
                    ranges[i].setPosition(coordinatePosition(selectorCoordinates[i]).x + BOXDIMENSIONS / 2, coordinatePosition(selectorCoordinates[i]).y + BOXDIMENSIONS / 2);
                    ranges[i].setOrigin(ranges[i].getRadius(), ranges[i].getRadius());
                    visibleRanges[i] = true;
                    break;
                }
            }

            if (showRange == false)
            {
                visibleRanges[i] = false;
            }
        }

        if(players == both)
        {
            if ((sf::Keyboard::isKeyPressed(settings.leftPlayer.speed) && sf::Keyboard::isKeyPressed(settings.rightPlayer.speed)) || fastForwardDown(mousePos))
                speedUp = settings.fastForwardSpeed;
            else
                speedUp = 1;
        }
        else if (players == left)
        {
            visibleRanges[1] = false;
            if (sf::Keyboard::isKeyPressed(settings.leftPlayer.speed) || fastForwardDown(mousePos))
                speedUp = settings.fastForwardSpeed;
            else
                speedUp = 1;
        }
        else
        {
            visibleRanges[0] = false;
            if (sf::Keyboard::isKeyPressed(settings.rightPlayer.speed) || fastForwardDown(mousePos))
                speedUp = settings.fastForwardSpeed;
            else
                speedUp = 1;
        }

        for (int a = 1; a <= speedUp; ++a)      //things that can be sped up
        {
            for(int b = 0; b < 2; ++b)
            {
                for(unsigned int i = 0; i < creeps[b].size(); ++i)  //update creeps
                {
                    if (creeps[b][i]->isDead())
                    {
                        delete creeps[b][i];
                        creeps[b][i] = NULL;
                        creeps[b].erase(creeps[b].begin() + i);
                        --i;
                        continue;
                    }
                    creeps[b][i]->update();
                }
            }

            for(unsigned int i = 0; i < towers.size(); ++i)     //update towers
            {
                Projectile * temp = towers[i]->update();
                if (temp != NULL)
                {
                    projectiles.push_back(temp);
                }
            }

            for (unsigned int i = 0; i < projectiles.size(); ++i)   //update projectiles
            {
                if (projectiles[i]->isDead())
                {
                    delete projectiles[i];
                    projectiles[i] = NULL;
                    projectiles.erase(projectiles.begin() + i);
                    --i;
                    continue;
                }
                projectiles[i]->update();
            }

            //update timer

            time += 1.0 / FPS;
            timer.setString(formatTime(floor(time)));
            timer.setOrigin(timer.getGlobalBounds().width / 2, timer.getGlobalBounds().height / 2);
            timer.setPosition(XRES / 2, timer.getPosition().y);
            timerBar.setSize({(float)(fmod(time + 30.0, 30.0) / 30.0 * 80.0), timerBar.getSize().y});

            if (speedUp == settings.fastForwardSpeed)
                speedBackground.setFillColor(sf::Color::Red);
            else
                speedBackground.setFillColor(sf::Color::Blue);

            speedUpAnimation++;
            if(speedUpAnimation > speedBackgroundTexture.getSize().x - 80)
                speedUpAnimation = 0;
            speedBackground.setTextureRect(sf::IntRect(speedUpAnimation, 0, speedBackground.getSize().x, speedBackground.getSize().y));
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
    {
        if (prevEscape == false)
        {
            resume.setVisible(!paused);
            exit.setVisible(!paused);
            paused = !paused;
        }
        prevEscape = true;
    }
    else
    {
        prevEscape = false;
    }

    return 0;
}

void Game::mouseSelector(sf::Vector2i mousePos)
{
    if (settings.enableMouse == true && players != both)
    {
        if (mousePos != prevMouse)
        {
            if (selected[players])
            {
                for (int i = 0; i < 4; ++i)
                {
                    if (gameButtons[players][4 + i].getHovered())
                    {
                        middleCoordinates[players] = i;
                    }
                }
            }
            else
            {
                sf::Vector2i tempCoordinate = gridPosition(mousePos);
                if(!(tempCoordinate.x < 0 || tempCoordinate.x >= GRIDX * 2 + MIDDLE || tempCoordinate.y < 0 || tempCoordinate.y >= GRIDY))
                {
                    selectorCoordinates[players] = tempCoordinate;
                }
            }
        }
        prevMouse = mousePos;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!(mousePos.x > gameButtons[players][4].getPosition().x && mousePos.x < gameButtons[players][7].getPosition().x + gameButtons[players][7].getSize().x && mousePos.y > gameButtons[players][4].getPosition().y && mousePos.y < gameButtons[players][4].getPosition().y + gameButtons[players][4].getSize().y))
            {       //click outside the box created by the 4 middle buttons
                selected[players] = false;
                middleCoordinates[players] = 0;
                buttonSelector[players].setPosition(gameButtons[players][4].getPosition());
            }

            if(players == left)
            {
                if (selectorCoordinates[0] == gridPosition(mousePos))
                {
                    if (selectorCoordinates[0].x < GRIDX)
                    {
                        selected[0] = true;
                        newTower(selectorCoordinates[0]);
                    }
                    else
                    {
                        //error message
                    }
                }
            }
            if(players == right)
            {
                if (selectorCoordinates[1] == gridPosition(mousePos))
                {
                    if (selectorCoordinates[1].x > GRIDX + MIDDLE - 1)
                    {
                        selected[1] = true;
                        newTower(selectorCoordinates[1]);
                    }
                    else
                    {
                        //error message
                    }
                }
            }
        }
    }
}

void Game::keyboardSelector(sf::Vector2i mousePos)
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
            {
                if (selected[i] == false)
                {
                    selectorCoordinates[i].y -= 1;
                }
            }
            prevKeys[i].up = true;
        }
        else
        {
            prevKeys[i].up = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.down))
        {
            if(prevKeys[i].down == false)
            {
                if (selected[i] == false)
                {
                    selectorCoordinates[i].y += 1;

                }
            }
            prevKeys[i].down = true;
        }
        else
        {
            prevKeys[i].down = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.left))
        {
            if(prevKeys[i].left == false)
            {
                if (selected[i] == false)
                {
                    selectorCoordinates[i].x -= 1;
                }
                else
                {
                    middleCoordinates[i] -= 1;
                    if (middleCoordinates[i] < 0)
                    {
                        middleCoordinates[i] = 3;
                    }
                }

            }
            prevKeys[i].left = true;
        }
        else
        {
            prevKeys[i].left = false;
        }
        if(sf::Keyboard::isKeyPressed(temp.right))
        {
            if(prevKeys[i].right == false)
            {
                if (selected[i] == false)
                {
                    selectorCoordinates[i].x += 1;
                }
                else
                {
                    middleCoordinates[i] += 1;
                    if (middleCoordinates[i] > 3)
                    {
                        middleCoordinates[i] = 0;
                    }
                }

            }
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
                if (selected[i])
                {
                            //BUTTON CLICKED
                }
                else
                {
                    if (i == 0) //left
                    {
                        if (selectorCoordinates[0].x < GRIDX)
                        {
                            newTower(selectorCoordinates[0]);
                            selected[i] = true;
                            //BUTTON CLICKED
                        }
                        else
                        {
                            //error message
                        }
                    }
                    if (i == 1) //right
                    {
                        if (selectorCoordinates[1].x > GRIDX + MIDDLE - 1)
                        {
                            newTower(selectorCoordinates[1]);
                            selected[i] = true;
                            //BUTTON CLICKED
                        }
                        else
                        {
                            //error message
                        }
                    }
                }
            }
            prevKeys[i].select = true;
        }
        else
        {
            prevKeys[i].select = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            creeps[0].push_back(new Creep(distancesRight, 0));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            creeps[1].push_back(new Creep(distancesLeft, 1));
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
            for (int a = 0; a < 2; ++a)
            {
                for (unsigned int b = 0; b < creeps[a].size(); ++b)
                {
                    if (i == creeps[a][b]->getCoordinates())
                    {
                        return;
                    }
                }
            }
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
                    if (i.x < GRIDX)
                    {
                        towers.push_back(new Tower(&creeps[1]));
                    }
                    else
                    {
                        towers.push_back(new Tower(&creeps[0]));
                    }
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

std::string Game::formatTime(int i)
{
    char temp[5];
    std::string time;

    if (i < 0)
        time += '-';
    sprintf(temp, "%d", i / 60);
    time += temp;
    time += ':';
    if (abs(i % 60) < 10)
        time += '0';
    sprintf(temp, "%d", abs(i % 60));
    time += temp;

    return time;
}

bool Game::fastForwardDown(sf::Vector2i mousePos)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (fastForward.getGlobalBounds().contains((sf::Vector2f)mousePos))
        {
            return true;
        }
    }

    return false;
}

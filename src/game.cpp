#include "game.h"

const char * const Game::baseStats[] = {"Tower 1\n", "Tower 2\n", "Tower 3\n", ""};

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
    pauseText.setCharacterSize(30);
    pauseText.setColor(sf::Color::White);
    pauseText.setPosition(XRES / 2, 100);

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
        otherButtonSelector[i].setTexture(&selectorTextures[i]);

        for(int a = 0; a < 4; ++a)  //creep queue
        {
            int offset = 180;
            int spacing = 5;
            if (i == 1)
            {
                offset = XRES - (offset + 3 * (60 + spacing) + 60);
            }
            gameButtons[i][a].initialize(60, 40);
            gameButtons[i][a].setPosition({(float)(offset + a * (gameButtons[i][a].getSize().x + spacing)) , 390});
            gameButtons[i][a].setVisible(true);
        }

        for(int a = 0; a < 4; ++a)  //buttons
        {
            int offset = 180;
            int spacing = 5;
            if (i == 1)
            {
                offset = XRES - (offset + 3 * (60 + spacing) + 60);
            }
            gameButtons[i][4 + a].initialize(60, 60);
            gameButtons[i][4 + a].setPosition({(float)(offset + a * (gameButtons[i][4 + a].getSize().x + spacing)), 440});
            gameButtons[i][4 + a].setVisible(true);
        }

        for(int a = 0; a < 3; ++a)  //creeps
        {
            int offset = 200;
            int spacing = 15;
            if (i == 1)
            {
                offset = XRES - (offset + 2 * (40 + spacing) + 40);
            }
            gameButtons[i][8 + a].initialize(40, 40);
            gameButtons[i][8 + a].setPosition({(float)(offset + a * (gameButtons[i][8 + a].getSize().x + spacing)), 510});
            gameButtons[i][8 + a].setVisible(true);
        }

        //money
        moneyText[i].setCharacterSize(24);
        moneyText[i].setColor(sf::Color::Black);
        moneyText[i].setString("$100");
        int offset = 60;
        if (i == 0)
        {
            moneyText[i].setPosition(gameButtons[0][10].getPosition().x + offset, 510);
        }
        else
        {
            moneyText[i].setPosition((XRES / 2) + offset, 510);
        }

        //lives text
        livesText[i].setCharacterSize(18);
        livesText[i].setColor(sf::Color::Black);
        livesText[i].setString("Lives: 10");
        livesText[i].setPosition(moneyText[i].getPosition().x, 540);

        //notifications text
        notifications[i].setCharacterSize(24);
        notifications[i].setColor(sf::Color::Black);
        notifications[i].setString("test");
        if (i == 0)
        {
            notifications[i].setPosition(100, 335);
        }
        else
        {
            notifications[i].setOrigin(notifications[i].getGlobalBounds().width, 0);
            notifications[i].setPosition(XRES - 100, 335);
        }

        //info text
        info[i].setCharacterSize(12);
        info[i].setColor(sf::Color::Black);
        info[i].setString("");
        offset = 20;
        if (i == 0)
        {
            info[i].setPosition(offset, 390);
        }
        else
        {
            info[i].setPosition(gameButtons[i][3].getPosition().x + gameButtons[i][3].getSize().x + offset, 390);
        }
    }

    //cached textures
    for (int a = 1; a < 4; ++a) //tower icons
    {
        for (int b = 0; b < 4; ++b)
        {
            char temp[40];
            sprintf(temp, "resources/tower%d-%d.png", a, b);
            towerIcons[a - 1][b].loadFromFile(temp);
        }
    }

    sell.loadFromFile("resources/sell.png");
    unselected.loadFromFile("resources/unselected.png");

    for (int a = 0; a < 4; ++a)
    {
        char temp[40];
        sprintf(temp, "resources/creepQueue%d.png", a);
        creepQueueTextures[a].loadFromFile(temp);
    }

    for (int a = 0; a < 4; ++a)
    {
        char temp[40];
        sprintf(temp, "resources/creepList%d.png", a);
        creepList[a].loadFromFile(temp);
    }

    for (int a = 0; a < 4; ++a)
    {
        char temp[40];
        sprintf(temp, "resources/creepIcon%d.png", a);
        creepIcons[a].loadFromFile(temp);
    }

    transparent.loadFromFile("resources/transparent.png");

    ////////////////

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

void Game::newGame(Game::Players temp, sf::Color leftSelector, sf::Color rightSelector, sf::Color tempLeft, sf::Color tempRight)
{
    players = temp;

    selector[0].setFillColor(leftSelector);
    buttonSelector[0].setFillColor(leftSelector);
    otherButtonSelector[0].setFillColor(leftSelector);
    selectorCoordinates[0] = {0, GRIDY / 2};

    selector[1].setFillColor(rightSelector);
    buttonSelector[1].setFillColor(rightSelector);
    otherButtonSelector[1].setFillColor(rightSelector);
    selectorCoordinates[1] = {GRIDX * 2 + MIDDLE - 1, GRIDY / 2};
    selected[0] = selected[1] = false;
    outOfGrid[0] = outOfGrid[1] = false;

    ranges[0].setOutlineColor(leftSelector);
    ranges[1].setOutlineColor(rightSelector);
    visibleRanges[0] = false;
    visibleRanges[1] = false;

    buttonSelector[0].setSize(gameButtons[0][4].getSize());
    buttonSelector[1].setSize(gameButtons[1][4].getSize());
    buttonSelector[0].setPosition(gameButtons[0][4].getPosition());
    buttonSelector[1].setPosition(gameButtons[1][4].getPosition());

    middleCoordinates[0] = middleCoordinates[1] = 0;
    buttonCoordinates[0] = buttonCoordinates[1] = 0;

    money[0] = money[1] = 100;  //temp
    moneyText[0].setString("$100");
    moneyText[1].setString("$100");

    pauseText.setString("Paused");
    pauseText.setOrigin(pauseText.getGlobalBounds().width / 2, pauseText.getGlobalBounds().height / 2);

    lives[0] = lives[1] = 10;
    livesText[0].setString("Lives: 10");
    livesText[1].setString("Lives: 10");

    notificationTimer[0] = notificationTimer[1] = 0;

    prevMouse = {0, 0};

    leftColor = tempLeft;
    rightColor = tempRight;

    prevKeys[0] = prevKeys[1] = {false, false, false, false, false, false, false, false, false, false};

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

    for (int i = 0; i < 2; ++i)
    {
        creepStats[i][0].amount = 5;
        creepStats[i][0].cooldown = 0;
        creepStats[i][0].hp = 100;
        creepStats[i][0].speed = 2;
        creepStats[i][0].timeLeft = 0;
        creepStats[i][0].type = 0;

        creepStats[i][1].amount = 5;
        creepStats[i][1].cooldown = 0;
        creepStats[i][1].hp = 50;
        creepStats[i][1].speed = 4;
        creepStats[i][1].timeLeft = 0;
        creepStats[i][1].type = 1;

        creepStats[i][2].amount = 5;
        creepStats[i][2].cooldown = 0;
        creepStats[i][2].hp = 200;
        creepStats[i][2].speed = 1;
        creepStats[i][2].timeLeft = 0;
        creepStats[i][2].type = 2;

        creepStats[i][3].amount = 5;
        creepStats[i][3].cooldown = 0;
        creepStats[i][3].hp = 50;
        creepStats[i][3].speed = 2;
        creepStats[i][3].timeLeft = 0;
        creepStats[i][3].type = 3;

        creepQueue[i][0] = &creepStats[i][0];
        creepQueue[i][1] = &creepStats[i][1];   //temp, beginning should all be type 0
        creepQueue[i][2] = &creepStats[i][2];
        creepQueue[i][3] = &creepStats[i][3];

        interval[i] = timeLeft[i] = amountLeft[i] = 0;
    }

    time = -30;
    wave = 0;

    calculateDistances();
    updateButtons(0);
    updateButtons(1);

    for (int a = 0; a < GRIDX * 2 + MIDDLE; ++a)
    {
        for (int b = 0; b < GRIDY; ++b)
        {
            flyingLeft[a][b] = distancesLeft[a][b];
            flyingRight[a][b] = distancesRight[a][b];
        }
    }

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
    initializeGrid(temp, leftColor, rightColor);     //temp colours

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
        for(int a = 0; a < 4; ++a)
        {
            gameButtons[i][a].draw(temp);
        }
    }

    for(int i = begin; i < end; ++i)
    {
        if (selected[i])
        {
            temp->draw(buttonSelector[i]);
        }

        if(outOfGrid[i])
        {
            temp->draw(otherButtonSelector[i]);
        }
        else
        {
            temp->draw(selector[i]);
        }

        for(int a = 4; a < 11; ++a)
        {
            gameButtons[i][a].draw(temp);
        }

        if (notificationTimer[i] > 0)
        {
            temp->draw(notifications[i]);
        }

        if (visibleRanges[i])
        {
            temp->draw(ranges[i]);
        }

        temp->draw(moneyText[i]);
        temp->draw(livesText[i]);
        temp->draw(info[i]);
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
        temp->draw(pauseText);
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

            otherButtonSelector[i].setSize(gameButtons[i][buttonCoordinates[i]].getSize());
            otherButtonSelector[i].setPosition(gameButtons[i][buttonCoordinates[i]].getPosition());

            bool somethingClicked = false;

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
                                buttonPressed(i, a - 4);
                            }
                        }
                        else if (a == 0) //current creep type in queue, cannot do anything with taht
                        {

                        }
                        else
                        {
                            selected[i] = true;
                            middleCoordinates[i] = 0;
                        }
                    }
                    somethingClicked = true;
                }
            }
            if (somethingClicked)
            {
                updateButtons(i);
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

            //info text
            if (selected[i])
            {
                if (outOfGrid[i])   //on creep queue or creep list
                {
                    if (buttonCoordinates[i] < 4)      //creep queue
                    {
                        info[i].setString(creepData(i, middleCoordinates[i]));
                    }
                    else        //creep list
                    {
                        info[i].setString(creepUpgrade(i, buttonCoordinates[i] - 7));
                    }
                }
                else    //in grid
                {
                    if (towerAt(selectorCoordinates[i]) == NULL)
                    {
                        info[i].setString(baseStats[middleCoordinates[i]]);
                    }
                    else
                    {
                        info[i].setString(towerAt(selectorCoordinates[i])->getUpgradeInfo(middleCoordinates[i]));
                    }
                }
            }
            else    //nothing is selected
            {
                if (outOfGrid[i])
                {
                    if (buttonCoordinates[i] < 4)      //creep queue
                    {
                        info[i].setString(creepData(i, creepQueue[i][buttonCoordinates[i]]->type));     //show stats of creep in that spot in queue
                    }
                    else        //creep list
                    {
                        info[i].setString(creepData(i, buttonCoordinates[i] - 7));
                    }
                }
                else        //in grid
                {
                    if (towerAt(selectorCoordinates[i]) == NULL)
                    {
                        info[i].setString("");
                    }
                    else
                    {
                        info[i].setString(towerAt(selectorCoordinates[i])->getCurrentInfo());
                    }
                }
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
            std::vector <sf::Vector2i> temp;

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
                    int status = creeps[b][i]->update();
                    if (status == 1)     //explode!
                    {
                        temp.push_back(gridPosition((sf::Vector2i)creeps[b][i]->getPosition()));
                    }
                    else if (status == 2)
                    {
                        //reached end
                        lives[abs(b - 1)]--;
                    }
                }
            }

            for (unsigned int i = 0; i < temp.size(); ++i)
            {
                explode(temp[i]);
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

            //spawn creeps

            for (int i = 0; i < 2; ++i)
            {
                for (int a = 0; a < 4; ++a)
                {
                    if (creepStats[i][a].timeLeft > 0)
                    {
                        creepStats[i][a].timeLeft--;
                    }
                }

                if (amountLeft[i] > 0)
                {
                    if (timeLeft[i] > 0)
                    {
                        timeLeft[i]--;
                    }
                    else    //spawn new creep
                    {
                        if (i == 0)
                        {
                            if (creepQueue[0][0]->type != 3)
                            {
                                creeps[0].push_back(new Creep(distancesRight, 0, creepQueue[0][0]->type, creepQueue[0][0]->speed, creepQueue[0][0]->hp));
                            }
                            else
                            {
                                creeps[0].push_back(new Creep(flyingRight, 0, creepQueue[0][0]->type, creepQueue[0][0]->speed, creepQueue[0][0]->hp));
                            }
                        }
                        else
                        {
                            if (creepQueue[1][0]->type != 3)
                            {
                                creeps[1].push_back(new Creep(distancesLeft, 1, creepQueue[1][0]->type, creepQueue[1][0]->speed, creepQueue[1][0]->hp));
                            }
                            else
                            {
                                creeps[1].push_back(new Creep(flyingLeft, 1, creepQueue[1][0]->type, creepQueue[1][0]->speed, creepQueue[1][0]->hp));
                            }
                        }
                        timeLeft[i] = interval[i];
                        amountLeft[i]--;
                    }
                }
            }

            //update timer

            time += 1.0 / FPS;
            timer.setString(formatTime(floor(time)));
            timer.setOrigin(timer.getGlobalBounds().width / 2, timer.getGlobalBounds().height / 2);
            timer.setPosition(XRES / 2, timer.getPosition().y);
            timerBar.setSize({(float)(fmod(time + 30.0, 30.0) / 30.0 * 80.0), timerBar.getSize().y});

            if (time > wave * 30)   //new wave
            {
                wave++;
                for (int i = 0; i < 2; ++i)
                {
                    //move up things in the queue
                    creepQueue[i][0] = creepQueue[i][1];
                    creepQueue[i][1] = creepQueue[i][2];
                    creepQueue[i][2] = creepQueue[i][3];
                    creepQueue[i][3] = &creepStats[i][0];   //latest in queue should be the default creep type

                    amountLeft[i] = creepQueue[i][0]->amount;
                    interval[i] = (20.0 / creepQueue[i][0]->amount) * FPS;  //spawn creeps over 20 seconds
                    timeLeft[i] = 0;

                    creepStats[i][0].hp += 50;
                    creepStats[i][0].amount++;

                    updateButtons(i);
                }
            }

            if (speedUp == settings.fastForwardSpeed)
                speedBackground.setFillColor(sf::Color::Red);
            else
                speedBackground.setFillColor(sf::Color::Blue);

            speedUpAnimation++;
            if(speedUpAnimation > speedBackgroundTexture.getSize().x - 80)
                speedUpAnimation = 0;
            speedBackground.setTextureRect(sf::IntRect(speedUpAnimation, 0, speedBackground.getSize().x, speedBackground.getSize().y));
        }

        for (int i = 0; i < 2; ++i) //update money text and lives text and notifications
        {
            char temp[20];
            sprintf(temp, "$%d", money[i]);
            moneyText[i].setString(temp);

            sprintf(temp, "Lives: %d", lives[i]);
            livesText[i].setString(temp);

            if (lives[i] <= 0)
            {
                //someone wins
                paused = true;
                resume.setVisible(false);
                exit.setVisible(true);

                char temp[50];

                if (i == 0)
                {
                    sprintf(temp, "Right side wins after %d waves!", wave);
                }
                else
                {
                    sprintf(temp, "Left side wins after %d waves!", wave);
                }

                if (lives[0] <= 0 && lives[1] <= 0)
                {
                    sprintf(temp, "It's a tie after %d waves!", wave);
                }

                pauseText.setString(temp);
                pauseText.setOrigin(pauseText.getGlobalBounds().width / 2, pauseText.getGlobalBounds().height / 2);
            }

            if (notificationTimer[i] > 0)
            {
                notificationTimer[i]--;
            }
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
                    outOfGrid[players] = false;
                }
                else
                {
                    for (int i = 0; i < 4; ++i) //check top row
                    {
                        if (gameButtons[players][i].getHovered())
                        {
                            outOfGrid[players] = true;
                            buttonCoordinates[players] = i;
                        }
                    }
                    for (int i = 8; i < 11; ++i) //check bottom row
                    {
                        if (gameButtons[players][i].getHovered())
                        {
                            outOfGrid[players] = true;
                            buttonCoordinates[players] = i;
                        }
                    }
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
                        middleCoordinates[0] = 0;
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
                        middleCoordinates[1] = 0;
                    }
                    else
                    {
                        //error message
                    }
                }
            }
            updateButtons(players);
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
                    if (outOfGrid[i])
                    {
                        if (buttonCoordinates[i] > 7)
                        {
                            if (i == 0)
                            {
                                buttonCoordinates[i] -= 8;
                            }
                            else
                            {
                                buttonCoordinates[i] -= 7;
                            }
                        }
                        else if (buttonCoordinates[i] < 4)
                        {
                            int temp = 0;
                            if (i == 1) //right
                            {
                                temp = 10;
                            }

                            if (buttonCoordinates[i] == 0)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = GRIDY - 1;
                                selectorCoordinates[i].x = 3 + temp;
                                if (i == 0) //patched up
                                {
                                    selectorCoordinates[i].x = 4;
                                }
                            }
                            else if (buttonCoordinates[i] == 1)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = GRIDY - 1;
                                selectorCoordinates[i].x = 5 + temp;
                            }
                            else if (buttonCoordinates[i] == 2)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = GRIDY - 1;
                                selectorCoordinates[i].x = 7 + temp;
                            }
                            else if (buttonCoordinates[i] == 3)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = GRIDY - 1;
                                selectorCoordinates[i].x = 8 + temp;
                            }
                        }
                    }
                    else
                    {
                        if (selectorCoordinates[i].y == 0)
                        {
                            if (i == 0) //left
                            {
                                if (selectorCoordinates[i].x == 3 || selectorCoordinates[i].x == 4)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 8;
                                }
                                else if (selectorCoordinates[i].x == 5)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 9;
                                }
                                else if (selectorCoordinates[i].x == 6 || selectorCoordinates[i].x == 7)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 10;
                                }
                                else if (selectorCoordinates[i].x == 8 || selectorCoordinates[i].x == 9)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 3;
                                }
                                else
                                {
                                    selectorCoordinates[i].y -= 1;
                                }
                            }
                            else    //right
                            {
                                if (selectorCoordinates[i].x == 13 || selectorCoordinates[i].x == 14)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 0;
                                }
                                else if (selectorCoordinates[i].x == 15 || selectorCoordinates[i].x == 16)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 8;
                                }
                                else if (selectorCoordinates[i].x == 17)    //the messed up location is mirrored to be 2nd from the outside
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 9;
                                }
                                else if (selectorCoordinates[i].x == 18 || selectorCoordinates[i].x == 19)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 10;
                                }
                                else
                                {
                                    selectorCoordinates[i].y -= 1;
                                }
                            }
                        }
                        else
                        {
                            selectorCoordinates[i].y -= 1;
                        }
                    }
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
                    if (outOfGrid[i])
                    {
                        if (buttonCoordinates[i] < 3 && i == 0)
                        {
                            buttonCoordinates[i] += 8;
                        }
                        else if (buttonCoordinates[i] > 0 && buttonCoordinates[i] < 4 && i == 1)
                        {
                            buttonCoordinates[i] += 7;
                        }
                        else
                        {
                            if (buttonCoordinates[i] == 8)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = 0;
                                if (i == 0)
                                {
                                    selectorCoordinates[i].x = 4;
                                }
                                else
                                {
                                    selectorCoordinates[i].x = 15;
                                }
                            }
                            else if (buttonCoordinates[i] == 9)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = 0;
                                if (i == 0)
                                {
                                    selectorCoordinates[i].x = 5;
                                }
                                else
                                {
                                    selectorCoordinates[i].x = 17;
                                }
                            }
                            else if (buttonCoordinates[i] == 10)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = 0;
                                if (i == 0)
                                {
                                    selectorCoordinates[i].x = 7;
                                }
                                else
                                {
                                    selectorCoordinates[i].x = 18;
                                }
                            }
                            else if (buttonCoordinates[i] == 3 && i == 0)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = 0;
                                selectorCoordinates[i].x = 8;
                            }
                            else if (buttonCoordinates[i] == 0 && i == 1)
                            {
                                outOfGrid[i] = false;
                                selectorCoordinates[i].y = 0;
                                selectorCoordinates[i].x = 14;
                            }
                        }
                    }
                    else
                    {
                        if (selectorCoordinates[i].y == GRIDY - 1)
                        {
                            if (i == 0) //left
                            {
                                if (selectorCoordinates[i].x == 3 || selectorCoordinates[i].x == 4)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 0;
                                }
                                else if (selectorCoordinates[i].x == 5)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 1;
                                }
                                else if (selectorCoordinates[i].x == 6 || selectorCoordinates[i].x == 7)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 2;
                                }
                                else if (selectorCoordinates[i].x == 8 || selectorCoordinates[i].x == 9)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 3;
                                }
                                else
                                {
                                    selectorCoordinates[i].y += 1;
                                }
                            }
                            else    //right
                            {
                                if (selectorCoordinates[i].x == 13 || selectorCoordinates[i].x == 14)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 0;
                                }
                                else if (selectorCoordinates[i].x == 15 || selectorCoordinates[i].x == 16)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 1;
                                }
                                else if (selectorCoordinates[i].x == 17)    //the messed up location is mirrored to be 2nd from the outside
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 2;
                                }
                                else if (selectorCoordinates[i].x == 18 || selectorCoordinates[i].x == 19)
                                {
                                    outOfGrid[i] = true;
                                    buttonCoordinates[i] = 3;
                                }
                                else
                                {
                                    selectorCoordinates[i].y += 1;
                                }
                            }
                        }
                        else
                        {
                            selectorCoordinates[i].y += 1;
                        }
                    }
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
                    if (outOfGrid[i])
                    {
                        buttonCoordinates[i] -= 1;
                        if (buttonCoordinates[i] == -1)
                        {
                            buttonCoordinates[i] = 3;
                        }
                        if (buttonCoordinates[i] == 7)
                        {
                            buttonCoordinates[i] = 10;
                        }
                    }
                    else
                    {
                        selectorCoordinates[i].x -= 1;
                    }
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
                    if (outOfGrid[i])
                    {
                        buttonCoordinates[i] += 1;
                        if (buttonCoordinates[i] == 4)
                        {
                            buttonCoordinates[i] = 0;
                        }
                        if (buttonCoordinates[i] == 11)
                        {
                            buttonCoordinates[i] = 8;
                        }
                    }
                    else
                    {
                        selectorCoordinates[i].x += 1;
                    }
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
                    buttonPressed(i, middleCoordinates[i]);
                }
                else
                {
                    if (outOfGrid[i])
                    {
                        if (buttonCoordinates[i] != 0)  //0 is selected current creep type in queue, cannot do anything with that
                        {
                            selected[i] = true;
                            middleCoordinates[i] = 0;
                        }
                    }
                    else
                    {
                        if (i == 0) //left
                        {
                            if (selectorCoordinates[0].x < GRIDX)
                            {
                                selected[i] = true;
                                middleCoordinates[i] = 0;
                            }
                            else
                            {
                                //trying to select enemy tower
                            }
                        }
                        if (i == 1) //right
                        {
                            if (selectorCoordinates[1].x > GRIDX + MIDDLE - 1)
                            {
                                selected[i] = true;
                                middleCoordinates[i] = 0;
                            }
                            else
                            {
                                //trying to select enemy tower
                            }
                        }
                    }
                }
                updateButtons(i);
            }
            prevKeys[i].select = true;
        }
        else
        {
            prevKeys[i].select = false;
        }

        if (sf::Keyboard::isKeyPressed(temp.back))
        {
            if(prevKeys[i].back == false)
            {
                selected[i] = false;
                updateButtons(i);
            }

            prevKeys[i].back = true;
        }
        else
        {
            prevKeys[i].back = false;
        }

        if (sf::Keyboard::isKeyPressed(temp.hotkey1))
        {
            if(prevKeys[i].hotkey1 == false)
            {
                buttonPressed(i, 0);
            }

            prevKeys[i].hotkey1 = true;
        }
        else
        {
            prevKeys[i].hotkey1 = false;
        }

        if (sf::Keyboard::isKeyPressed(temp.hotkey2))
        {
            if(prevKeys[i].hotkey2 == false)
            {
                buttonPressed(i, 1);
            }

            prevKeys[i].hotkey2 = true;
        }
        else
        {
            prevKeys[i].hotkey2 = false;
        }

        if (sf::Keyboard::isKeyPressed(temp.hotkey3))
        {
            if(prevKeys[i].hotkey3 == false)
            {
                buttonPressed(i, 2);
            }

            prevKeys[i].hotkey3 = true;
        }
        else
        {
            prevKeys[i].hotkey3 = false;
        }

        if (sf::Keyboard::isKeyPressed(temp.hotkey4))
        {
            if(prevKeys[i].hotkey4 == false)
            {
                buttonPressed(i, 3);
            }

            prevKeys[i].hotkey4 = true;
        }
        else
        {
            prevKeys[i].hotkey4 = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            creeps[0].push_back(new Creep(distancesRight, 0, 0, 1, 50));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        {
            creeps[1].push_back(new Creep(distancesLeft, 1, 0, 1, 50));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            money[0] += 100;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Multiply))
        {
            money[1] += 100;
        }

        if (selectorCoordinates[i].y < 0)
        {
            selectorCoordinates[i].y = GRIDY - 1;
        }
        if (selectorCoordinates[i].y > GRIDY - 1)
        {
            selectorCoordinates[i].y = 0;
        }
        if (selectorCoordinates[i].x < 0)
        {
            selectorCoordinates[i].x = GRIDX * 2 + MIDDLE - 1;
        }
        if (selectorCoordinates[i].x > GRIDX * 2 + MIDDLE - 1)
        {
            selectorCoordinates[i].x = 0;
        }
    }
}

void Game::newTower(sf::Vector2i i, int type)
{
    int temp = 1;
    if (i.x < GRIDX)
    {
        temp = 0;
    }

    //does not allow creating tower outside of grid
    if (i.x >= 0 && i.x < GRIDX * 2 + MIDDLE && i.y >= 0 && i.y < GRIDY)
    {
        if ((i.x == 0 && i.y == GRIDY / 2) || (i.x == GRIDX * 2 + MIDDLE - 1 && i.y == GRIDY / 2))   //trying to place tower on spawn points
        {
            notify(temp, "Cannot block path");
        }
        else if(i.x >= GRIDX && i.x < GRIDX + MIDDLE)   //trying to place in middle
        {

        }
        else
        {
            if (money[temp] >= towerStats[type][0][0].cost)
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
                if (map[i.x][i.y] == false) //if the spot is empty
                {
                    map[i.x][i.y] = true;
                    calculateDistances();
                    if (distancesRight[0][GRIDY / 2] == EMPTY)
                    {
                        //no path available, new tower is blocking
                        map[i.x][i.y] = false;
                        calculateDistances();

                        notify(temp, "Cannot block path");
                    }
                    else    //everything OK, build
                    {
                        towers.push_back(new Tower(&creeps[abs(temp - 1)], &creeps[temp], type));
                        towers[towers.size() - 1]->setCoordinates(i);
                        money[temp] -= towerStats[type][0][0].cost;
                    }
                }
            }
            else
            {
                notify(temp, "Not enough money");
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

void Game::buttonPressed(int player, int button)
{
    if (outOfGrid[player])
    {
        if (buttonCoordinates[player] < 4 && buttonCoordinates[player] > 0)      //creep queue, but cannot change first one (since it is current one)
        {
            creepQueue[player][buttonCoordinates[player]] = &creepStats[player][button];
            selected[player] = false;
        }
        else    //creep list
        {
            if (button == 0)    //only 1 upgrade available per creep
            {
                //upgrade
            }
        }
    }
    else
    {
        if (button >= 0 && button <= 2)     //create or upgrade
        {
            if (towerAt(selectorCoordinates[player]) == NULL)   //create
            {
                if (player == 0)
                {
                    if (selectorCoordinates[player].x < GRIDX)
                    {
                        newTower(selectorCoordinates[player], button);
                    }
                    else
                    {
                        notify(player, "You can only build on your side");
                    }
                }
                else
                {
                    if (selectorCoordinates[player].x > GRIDX + MIDDLE - 1)
                    {
                        newTower(selectorCoordinates[player], button);
                    }
                    else
                    {
                        notify(player, "You can only build on your side");
                    }
                }
                if (settings.selectAfterUpgrade == false)
                {
                    selected[player] = false;
                }
            }
            else    //upgrade
            {
                Tower * tempTower = towerAt(selectorCoordinates[player]);
                if (tempTower->getType().z >= 3)
                {
                    //max lvl
                }
                else
                {
                    if (player == 0)
                    {
                        if (selectorCoordinates[player].x < GRIDX)
                        {
                            if (tempTower->getType().y != 0)
                            {
                                if (button == 0)  //upgrade secondary
                                {
                                    if (money[player] >= towerStats[tempTower->getType().x - 1][tempTower->getType().y][tempTower->getType().z + 1].cost)
                                    {
                                        money[player] -= towerStats[tempTower->getType().x - 1][tempTower->getType().y][tempTower->getType().z + 1].cost;
                                        tempTower->upgrade(button + 1);
                                    }
                                    else
                                    {
                                        notify(player, "Not enough money");
                                    }
                                }
                            }
                            else    //new tower type
                            {
                                if (money[player] >= towerStats[tempTower->getType().x - 1][button + 1][0].cost)
                                {
                                    money[player] -= towerStats[tempTower->getType().x - 1][button + 1][0].cost;
                                    tempTower->upgrade(button + 1);
                                }
                                else
                                {
                                    notify(player, "Not enough money");
                                }
                            }
                        }
                        else
                        {
                            //trying to upgrade enemy tower
                        }
                    }
                    else
                    {
                        if (selectorCoordinates[player].x > GRIDX + MIDDLE - 1)
                        {
                            if (tempTower->getType().y != 0)
                            {
                                if (button == 0)  //upgrade secondary
                                {
                                    if (money[player] >= towerStats[tempTower->getType().x - 1][tempTower->getType().y][tempTower->getType().z + 1].cost)
                                    {
                                        money[player] -= towerStats[tempTower->getType().x - 1][tempTower->getType().y][tempTower->getType().z + 1].cost;
                                        tempTower->upgrade(button + 1);
                                    }
                                    else
                                    {
                                        notify(player, "Not enough money");
                                    }
                                }
                            }
                            else    //new tower type
                            {
                                if (money[player] >= towerStats[tempTower->getType().x - 1][button + 1][0].cost)
                                {
                                    money[player] -= towerStats[tempTower->getType().x - 1][button + 1][0].cost;
                                    tempTower->upgrade(button + 1);
                                }
                                else
                                {
                                    notify(player, "Not enough money");
                                }
                            }
                        }
                        else
                        {
                            //trying to upgrade enemy tower
                        }
                    }
                }
                if (settings.selectAfterUpgrade == false)
                {
                    selected[player] = false;
                }
            }
        }
        else if (button == 3)   //sell
        {
            if (player == 0)
            {
                if (selectorCoordinates[player].x < GRIDX)
                {
                    if (towerAt(selectorCoordinates[player]) != NULL)
                    {
                        removeTower(selectorCoordinates[player]);
                    }
                }
                else
                {
                    //trying to sell enemy tower
                }
            }
            else
            {
                if (selectorCoordinates[player].x > GRIDX + MIDDLE - 1)
                {
                    if (towerAt(selectorCoordinates[player]) != NULL)
                    {
                        removeTower(selectorCoordinates[player]);
                    }
                }
                else
                {
                    //trying to sell enemy tower
                }
            }
            selected[player] = false;
        }
    }
    updateButtons(player);
}

void Game::removeTower(sf::Vector2i i)
{
    for(unsigned int a = 0; a < towers.size(); ++a)
    {
        if (towers[a]->getCoordinates() == i)
        {
            delete towers[a];
            towers[a] = NULL;
            towers.erase(towers.begin() + a);
            map[i.x][i.y] = false;
            calculateDistances();
            return;
        }
    }
}

Tower * Game::towerAt(sf::Vector2i i)
{
    for(unsigned int a = 0; a < towers.size(); ++a)
    {
        if (towers[a]->getCoordinates() == i)
        {
            return towers[a];
        }
    }
    return NULL;
}

void Game::updateButtons(int player)
{
    if (outOfGrid[player])
    {
        if (selected[player])
        {
            if (buttonCoordinates[player] > 0 && buttonCoordinates[player] < 4)     //queue
            {
                for (int i = 0; i < 4; ++i)
                {
                     gameButtons[player][4 + i].setTexture(&creepIcons[i]);
                }
            }
            else        //creep list
            {
                //i guess show the upgrade avilable?
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                gameButtons[player][4 + i].setTexture(&unselected);
            }
        }
    }
    else
    {
        if (selected[player])
        {
            Tower * tempTower = towerAt(selectorCoordinates[player]);
            if (tempTower == NULL)  //no tower there yet, build new tower options
            {
                for (int i = 0; i < 3; ++i)
                {
                    gameButtons[player][4 + i].setTexture(&towerIcons[i][0]);
                }
                gameButtons[player][7].setTexture(&sell);
            }
            else        //tower already exists
            {
                sf::Vector3i tempType = tempTower->getType();

                if (tempType.y == 0)    //show the 3 advanced tower types
                {
                    for (int i = 0; i < 3; ++i)
                    {
                         gameButtons[player][4 + i].setTexture(&towerIcons[tempType.x - 1][i + 1]);
                    }
                }
                else        //upgrade!
                {
                    if (tempType.z >= 3)        //max level
                        gameButtons[player][4].setTexture(&unselected);
                    else
                        gameButtons[player][4].setTexture(&towerIcons[tempType.x - 1][tempType.y]);
                    gameButtons[player][5].setTexture(&unselected);
                    gameButtons[player][6].setTexture(&unselected);
                }

                gameButtons[player][7].setTexture(&sell);
            }
        }
        else
        {
            for (int i = 0; i < 4; ++i)
            {
                gameButtons[player][4 + i].setTexture(&unselected);
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        gameButtons[player][i].setTexture(&creepQueueTextures[creepQueue[player][i]->type]);
    }
    for (int i = 8; i < 11; ++i)
    {
        gameButtons[player][i].setTexture(&creepList[i - 7]);
    }

    if (wave == 0)
    {
        gameButtons[0][0].setTexture(&transparent);
        gameButtons[1][0].setTexture(&transparent);
    }
}

void Game::explode(sf::Vector2i i)
{
    for (int b = 0; b < 2; ++b)
    {
        for(unsigned int a = 0; a < creeps[b].size(); ++a)
        {
            if (gridPosition((sf::Vector2i)creeps[b][a]->getPosition()) == i)
            {
                creeps[b][a]->damage(99999);
            }
        }
    }

    removeTower(i);
    if (i.x > 0)
    {
        removeTower(sf::Vector2i(i.x - 1, i.y));
    }
    if (i.x < GRIDX * 2 + MIDDLE - 1)
    {
        removeTower(sf::Vector2i(i.x + 1, i.y));
    }
    if (i.y > 0)
    {
        removeTower(sf::Vector2i(i.x, i.y - 1));
    }
    if (i.y < GRIDY)
    {
        removeTower(sf::Vector2i(i.x, i.y + 1));
    }
}

void Game::notify(int side, std::string text, int seconds)
{
    notificationTimer[side] = seconds * FPS;
    notifications[side].setString(text);
    if (side == 1)
    {
        notifications[side].setOrigin(notifications[side].getGlobalBounds().width, 0);
    }
}

std::string Game::creepData(int side, int type)
{
    std::string temp1("");
    char temp2[200];
    sprintf(temp2, "Creep type %d", type);
    temp1 += temp2;
    return temp1;
}

std::string Game::creepUpgrade(int side, int type)
{
    std::string temp1("");
    char temp2[200];
    sprintf(temp2, "Creep type %d upgrade", type);
    temp1 += temp2;
    return temp1;
}

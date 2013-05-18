#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

const char * const Menu::keyNames[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Esc", "LCtrl", "LShift", "LAlt", "LOS", "RCtrl", "RShift", "RAlt", "ROS", "Menu", "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Space", "Return", "Backspace", "Tab", "PgUp", "PgDown", "End", "Home", "Insert", "Del", "Num+", "Num-", "Num*", "Num/", "Left", "Right", "Up", "Down", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};
const char * const Menu::hotkeyNames[] = {"left player up", "left player down", "left player left", "left player right", "left player select", "left player back", "left player fast forward", "left player hotkey 1", "left player hotkey 2", "left player hotkey 3", "left player hotkey 4", "right player up", "right player down", "right player left", "right player right", "right player select", "right player back", "right player fast forward", "right player hotkey 1", "right player hotkey 2", "right player hotkey 3", "right player hotkey 4"};

Menu::Menu()
{
    if (settings.doubleBuffered)
    {
        if(!canvas.create(XRES, YRES))
            printf("Error creating menu renderTexture\n");
    }

    readSettings();

    background.setSize({XRES, YRES});
    background.setPosition(0, 0);
    background.setFillColor(sf::Color::White);

    mainBackgroundTexture.loadFromFile("resources/menuBackground.png");
    settingsBackgroundTexture.loadFromFile("resources/settingsBackground.png");
    background.setTexture(&mainBackgroundTexture);

    bindBackground.setSize({XRES, YRES});
    bindBackground.setPosition({0, 0});
    bindBackground.setFillColor(sf::Color(0, 0, 0, 128));
    bindText.setColor(sf::Color::White);
    bindText.setCharacterSize(30);
    bindText.setPosition({XRES / 2, YRES / 2});

    isBinding = false;

    //MAIN MENU
    mainMenu.push_back(new Button());   //single player
    mainMenu[0]->initialize(100, 50);
    mainMenu[0]->setPosition({100, 225});
    mainMenu[0]->loadTexture("resources/singlePlayer.png");

    mainMenu.push_back(new Button());   //multi player
    mainMenu[1]->initialize(100, 50);
    mainMenu[1]->setPosition({100, 300});
    mainMenu[1]->loadTexture("resources/multiPlayer.png");

    mainMenu.push_back(new Button());   //options
    mainMenu[2]->initialize(100, 50);
    mainMenu[2]->setPosition({100, 375});
    mainMenu[2]->loadTexture("resources/settings.png");

    mainMenu.push_back(new Button());   //exit button
    mainMenu[3]->initialize(100, 50);
    mainMenu[3]->setPosition({100, 450});
    mainMenu[3]->loadTexture("resources/exit.png");

    //SETTINGS text

    settingsText.push_back(new sf::Text());     //music volume
    settingsText[0]->setColor(sf::Color::Black);
    settingsText[0]->setCharacterSize(30);
    settingsText[0]->setPosition(130, 70);

    settingsText.push_back(new sf::Text());     //music volume label
    settingsText[1]->setColor(sf::Color::Black);
    settingsText[1]->setCharacterSize(18);
    settingsText[1]->setString("Music volume");
    settingsText[1]->setPosition(50, 20);

    settingsText.push_back(new sf::Text());     //sfx volume
    settingsText[2]->setColor(sf::Color::Black);
    settingsText[2]->setCharacterSize(30);
    settingsText[2]->setPosition(130, 170);

    settingsText.push_back(new sf::Text());     //sfx volume label
    settingsText[3]->setColor(sf::Color::Black);
    settingsText[3]->setCharacterSize(18);
    settingsText[3]->setString("Effects volume");
    settingsText[3]->setPosition(50, 120);

    settingsText.push_back(new sf::Text());     //enable mouse label
    settingsText[4]->setColor(sf::Color::Black);
    settingsText[4]->setCharacterSize(18);
    settingsText[4]->setString("Enable mouse");
    settingsText[4]->setPosition(50, 220);

    settingsText.push_back(new sf::Text());     //select after upgrade label
    settingsText[5]->setColor(sf::Color::Black);
    settingsText[5]->setCharacterSize(18);
    settingsText[5]->setString("Keep selected after upgrade");
    settingsText[5]->setPosition(50, 320);

    settingsText.push_back(new sf::Text());     //left label
    settingsText[6]->setColor(sf::Color::Black);
    settingsText[6]->setCharacterSize(30);
    settingsText[6]->setString("Left");
    settingsText[6]->setPosition(350, 20);

    for (int i = 0; i < 11; ++i)    //left
    {
        settingsText.push_back(new sf::Text());
        settingsText[7 + i]->setColor(sf::Color::Black);
        settingsText[7 + i]->setCharacterSize(16);
        settingsText[7 + i]->setPosition(400, 70 + 40 * i);
    }

    settingsText.push_back(new sf::Text());     //right label
    settingsText[18]->setColor(sf::Color::Black);
    settingsText[18]->setCharacterSize(30);
    settingsText[18]->setString("Right");
    settingsText[18]->setPosition(750, 20);

    for (int i = 0; i < 11; ++i)    //right
    {
        settingsText.push_back(new sf::Text());
        settingsText[19 + i]->setColor(sf::Color::Black);
        settingsText[19 + i]->setCharacterSize(16);
        settingsText[19 + i]->setPosition(800, 70 + 40 * i);
    }

    //SETTINGS buttons

    settingsMenu.push_back(new Button());   //back button
    settingsMenu[0]->initialize(100, 50);
    settingsMenu[0]->setPosition({26, 500});
    settingsMenu[0]->loadTexture("resources/back.png");
    settingsMenu[0]->setVisible(false);

    settingsMenu.push_back(new Button());   //music down button
    settingsMenu[1]->initialize(50, 50);
    settingsMenu[1]->setPosition({30, 50});
    settingsMenu[1]->loadTexture("resources/leftButton.png");
    settingsMenu[1]->setVisible(false);

    settingsMenu.push_back(new Button());   //music up button
    settingsMenu[2]->initialize(50, 50);
    settingsMenu[2]->setPosition({180, 50});
    settingsMenu[2]->loadTexture("resources/rightButton.png");
    settingsMenu[2]->setVisible(false);

    settingsMenu.push_back(new Button());   //effects down button
    settingsMenu[3]->initialize(50, 50);
    settingsMenu[3]->setPosition({30, 150});
    settingsMenu[3]->loadTexture("resources/leftButton.png");
    settingsMenu[3]->setVisible(false);

    settingsMenu.push_back(new Button());   //effects up button
    settingsMenu[4]->initialize(50, 50);
    settingsMenu[4]->setPosition({180, 150});
    settingsMenu[4]->loadTexture("resources/rightButton.png");
    settingsMenu[4]->setVisible(false);

    settingsMenu.push_back(new Button());   //enable mouse button
    settingsMenu[5]->initialize(100, 50);
    settingsMenu[5]->setPosition({30, 250});
    settingsMenu[5]->setVisible(false);

    settingsMenu.push_back(new Button());   //select after upgrade button
    settingsMenu[6]->initialize(100, 50);
    settingsMenu[6]->setPosition({30, 350});
    settingsMenu[6]->setVisible(false);

    for (int i = 0; i < 11; ++i)    //left 7 - 17
    {
        settingsMenu.push_back(new Button());
        settingsMenu[7 + i]->initialize(25, 25);
        settingsMenu[7 + i]->setPosition({350, (float)(70 + 40 * i)});
        settingsMenu[7 + i]->loadTexture("resources/bindKey.png");
        settingsMenu[7 + i]->setVisible(false);
    }

    for (int i = 0; i < 11; ++i)    //right 18 - 28
    {
        settingsMenu.push_back(new Button());
        settingsMenu[18 + i]->initialize(25, 25);
        settingsMenu[18 + i]->setPosition({750, (float)(70 + 40 * i)});
        settingsMenu[18 + i]->loadTexture("resources/bindKey.png");
        settingsMenu[18 + i]->setVisible(false);
    }

    //SINGLE PLAYER
    singleMenu.push_back(new Button());   //back button
    singleMenu[0]->initialize(100, 50);
    singleMenu[0]->setPosition({26, 500});
    singleMenu[0]->loadTexture("resources/back.png");
    singleMenu[0]->setVisible(false);

    singleMenu.push_back(new Button());   //mission 1
    singleMenu[1]->initialize(400, 175);
    singleMenu[1]->setPosition({75, 50});
    singleMenu[1]->loadTexture("resources/mission1.png");
    singleMenu[1]->setVisible(false);

    singleMenu.push_back(new Button());   //mission 2
    singleMenu[2]->initialize(400, 175);
    singleMenu[2]->setPosition({549, 50});
    singleMenu[2]->loadTexture("resources/mission1.png");
    singleMenu[2]->setVisible(false);

    singleMenu.push_back(new Button());   //mission 3
    singleMenu[3]->initialize(400, 175);
    singleMenu[3]->setPosition({75, 275});
    singleMenu[3]->loadTexture("resources/mission1.png");
    singleMenu[3]->setVisible(false);

    singleMenu.push_back(new Button());   //mission 4
    singleMenu[4]->initialize(400, 175);
    singleMenu[4]->setPosition({549, 275});
    singleMenu[4]->loadTexture("resources/mission1.png");
    singleMenu[4]->setVisible(false);

    //MULTIPLAYER
    multiMenu.push_back(new Button());   //back button
    multiMenu[0]->initialize(100, 50);
    multiMenu[0]->setPosition({26, 500});
    multiMenu[0]->loadTexture("resources/back.png");
    multiMenu[0]->setVisible(false);

    multiMenu.push_back(new Button());   //temp button
    multiMenu[1]->initialize(100, 50);
    multiMenu[1]->setPosition({50, 50});
    multiMenu[1]->loadTexture("resources/back.png");
    multiMenu[1]->setVisible(false);

    updateSettings();
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Menu::~Menu()
{
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        delete mainMenu[i];
    }
    for(unsigned int i = 0; i < settingsMenu.size(); ++i)
    {
        delete settingsMenu[i];
    }
    for(unsigned int i = 0; i < settingsText.size(); ++i)
    {
        delete settingsText[i];
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

void Menu::draw(sf::RenderWindow * window)
{
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
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        mainMenu[i]->draw(temp);
    }
    for(unsigned int i = 0; i < settingsMenu.size(); ++i)
    {
        settingsMenu[i]->draw(temp);
    }
    for(unsigned int i = 0; i < singleMenu.size(); ++i)
    {
        singleMenu[i]->draw(temp);
    }
    for(unsigned int i = 0; i < multiMenu.size(); ++i)
    {
        multiMenu[i]->draw(temp);
    }

    if (settingsMenu[0]->getVisible())
    {
        for(unsigned int i = 0; i < settingsText.size(); ++i)
        {
            temp->draw(*settingsText[i]);
        }
    }
    if (multiMenu[0]->getVisible())
    {
        for(unsigned int i = 0; i < multiText.size(); ++i)
        {
            temp->draw(*multiText[i]);
        }
    }

    if (isBinding)
    {
        temp->draw(bindBackground);
        temp->draw(bindText);
    }

    if (settings.doubleBuffered)
    {
        canvas.display();
        drawable.setPosition(0, 0);
        drawable.setTexture(canvas.getTexture());
        window->draw(drawable);
    }
}

int Menu::update(sf::Vector2i mousePos)
{
    if (isBinding)
    {
        bindKey();
    }
    else
    {
        for(unsigned int i = 0; i < mainMenu.size(); ++i)
        {
            if(mainMenu[i]->update(mousePos))
            {
                switch(i)
                {
                    case 0: //single player
                        //return 1;
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(false);
                        }
                        for (unsigned int a = 0; a < singleMenu.size(); ++a)
                        {
                            singleMenu[a]->setVisible(true);
                        }
                        break;
                    case 1: //multi player
                        //return 2;
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(false);
                        }
                        for (unsigned int a = 0; a < multiMenu.size(); ++a)
                        {
                            multiMenu[a]->setVisible(true);
                        }
                        break;
                    case 2: //go to settings
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(false);
                        }
                        for (unsigned int a = 0; a < settingsMenu.size(); ++a)
                        {
                            settingsMenu[a]->setVisible(true);
                        }

                        background.setTexture(&settingsBackgroundTexture);
                        isBinding = false;
                        break;
                    case 3: //exit
                        return 10;
                        break;
                }
            }
        }

        for(unsigned int i = 0; i < settingsMenu.size(); ++i)
        {
            if (settingsMenu[i]->update(mousePos))
            {
                switch(i)
                {
                    case 0: //back
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(true);
                        }
                        for (unsigned int a = 0; a < settingsMenu.size(); ++a)
                        {
                            settingsMenu[a]->setVisible(false);
                        }
                        background.setTexture(&mainBackgroundTexture);
                        writeSettings();
                        break;
                    case 1:     //music down
                        settings.musicVolume--;
                        if (settings.musicVolume < 0)
                        {
                            settings.musicVolume = 0;
                        }
                        updateSettings();
                        break;
                    case 2:     //music up
                        settings.musicVolume++;
                        if (settings.musicVolume > 10)
                        {
                            settings.musicVolume = 10;
                        }
                        updateSettings();
                        break;
                    case 3:     //effects down
                        settings.effectVolume--;
                        if (settings.effectVolume < 0)
                        {
                            settings.effectVolume = 0;
                        }
                        updateSettings();
                        break;
                    case 4:     //effects up
                        settings.effectVolume++;
                        if (settings.effectVolume > 10)
                        {
                            settings.effectVolume = 10;
                        }
                        updateSettings();
                        break;
                    case 5:     //enable mouse
                        settings.enableMouse = !settings.enableMouse;
                        updateSettings();
                        break;
                    case 6:     //select after upgrade
                        settings.selectAfterUpgrade = !settings.selectAfterUpgrade;
                        updateSettings();
                        break;
                    default:
                        sprintf(bindMessage, "Press the escape key to exit.\n\nPress the new key for %s", hotkeyNames[i - 7]);
                        isBinding = true;
                        currentKey = i;
                        updateSettings();
                        break;
                }
            }
        }

        for (unsigned int i = 0; i < singleMenu.size(); ++i)
        {
            if(singleMenu[i]->update(mousePos))
            {
                switch(i)
                {
                    case 0: //back button
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(true);
                        }
                        for (unsigned int a = 0; a < singleMenu.size(); ++a)
                        {
                            singleMenu[a]->setVisible(false);
                        }
                        break;
                    case 1: //mission 1
                        return 1;
                        break;
                    case 2: //mission 2
                        return 1;
                        break;
                    case 3: //mission 3
                        return 1;
                        break;
                    case 4: //mission 4
                        return 1;
                        break;
                }
            }
        }

        for (unsigned int i = 0; i < multiMenu.size(); ++i)
        {
            if(multiMenu[i]->update(mousePos))
            {
                switch(i)
                {
                    case 0:
                        for (unsigned int a = 0; a < mainMenu.size(); ++a)
                        {
                            mainMenu[a]->setVisible(true);
                        }
                        for (unsigned int a = 0; a < multiMenu.size(); ++a)
                        {
                            multiMenu[a]->setVisible(false);
                        }
                        break;
                    case 1:
                        return 2;
                        break;
                }
            }
        }
    }

    return 0;
}

void Menu::readSettings()
{
    FILE * ifp = fopen("settings", "r");
    if (ifp != NULL)
    {       //format: effectvolume, musicvolume, enablemouse, selectafterupgrade, leftkeys, rightkeys
        fscanf(ifp, "%d\n%d\n%d\n%d", &settings.musicVolume, &settings.effectVolume, (int*)&settings.enableMouse, (int*)&settings.selectAfterUpgrade);
        fscanf(ifp, "%d\n%d\n%d\n%d\n%d\n%d\n%d", (int*)&settings.leftPlayer.up, (int*)&settings.leftPlayer.down, (int*)&settings.leftPlayer.left, (int*)&settings.leftPlayer.right, (int*)&settings.leftPlayer.select, (int*)&settings.leftPlayer.back, (int*)&settings.leftPlayer.speed);
        fscanf(ifp, "%d\n%d\n%d\n%d", (int*)&settings.leftPlayer.hotkey1, (int*)&settings.leftPlayer.hotkey2, (int*)&settings.leftPlayer.hotkey3, (int*)&settings.leftPlayer.hotkey4);
        fscanf(ifp, "%d\n%d\n%d\n%d\n%d\n%d\n%d", (int*)&settings.rightPlayer.up, (int*)&settings.rightPlayer.down, (int*)&settings.rightPlayer.left, (int*)&settings.rightPlayer.right, (int*)&settings.rightPlayer.select, (int*)&settings.rightPlayer.back, (int*)&settings.rightPlayer.speed);
        fscanf(ifp, "%d\n%d\n%d\n%d", (int*)&settings.rightPlayer.hotkey1, (int*)&settings.rightPlayer.hotkey2, (int*)&settings.rightPlayer.hotkey3, (int*)&settings.rightPlayer.hotkey4);

        fclose(ifp);
    }
    else
    {
        settings.musicVolume = 5;
        settings.effectVolume = 5;
        settings.enableMouse = true;
        settings.selectAfterUpgrade = false;

        settings.leftPlayer.up = sf::Keyboard::W;
        settings.leftPlayer.down = sf::Keyboard::S;
        settings.leftPlayer.left = sf::Keyboard::A;
        settings.leftPlayer.right = sf::Keyboard::D;
        settings.leftPlayer.select = sf::Keyboard::F;
        settings.leftPlayer.back = sf::Keyboard::G;
        settings.leftPlayer.speed = sf::Keyboard::Space;
        settings.leftPlayer.hotkey1 = sf::Keyboard::R;
        settings.leftPlayer.hotkey2 = sf::Keyboard::T;
        settings.leftPlayer.hotkey3 = sf::Keyboard::Y;
        settings.leftPlayer.hotkey4 = sf::Keyboard::U;

        settings.rightPlayer.up = sf::Keyboard::Up;
        settings.rightPlayer.down = sf::Keyboard::Down;
        settings.rightPlayer.left = sf::Keyboard::Left;
        settings.rightPlayer.right = sf::Keyboard::Right;
        settings.rightPlayer.select = sf::Keyboard::Numpad1;
        settings.rightPlayer.back = sf::Keyboard::Numpad2;
        settings.rightPlayer.speed = sf::Keyboard::Numpad0;
        settings.rightPlayer.hotkey1 = sf::Keyboard::Numpad4;
        settings.rightPlayer.hotkey2 = sf::Keyboard::Numpad5;
        settings.rightPlayer.hotkey3 = sf::Keyboard::Numpad6;
        settings.rightPlayer.hotkey4 = sf::Keyboard::Add;

        writeSettings();
    }
}

void Menu::writeSettings()
{
    FILE * ofp = fopen("settings", "w");
    fprintf(ofp, "%d\n%d\n%d\n%d\n", settings.musicVolume, settings.effectVolume, settings.enableMouse, settings.selectAfterUpgrade);
    fprintf(ofp, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", (int)settings.leftPlayer.up, (int)settings.leftPlayer.down, (int)settings.leftPlayer.left, (int)settings.leftPlayer.right, (int)settings.leftPlayer.select, (int)settings.leftPlayer.back, (int)settings.leftPlayer.speed, (int)settings.leftPlayer.hotkey1, (int)settings.leftPlayer.hotkey2, (int)settings.leftPlayer.hotkey3, (int)settings.leftPlayer.hotkey4);
    fprintf(ofp, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", (int)settings.rightPlayer.up, (int)settings.rightPlayer.down, (int)settings.rightPlayer.left, (int)settings.rightPlayer.right, (int)settings.rightPlayer.select, (int)settings.rightPlayer.back, (int)settings.rightPlayer.speed, (int)settings.rightPlayer.hotkey1, (int)settings.rightPlayer.hotkey2, (int)settings.rightPlayer.hotkey3, (int)settings.rightPlayer.hotkey4);
    fclose(ofp);
}

void Menu::updateSettings()
{
    char temp[50];
    sprintf(temp, "%d", settings.musicVolume);
    settingsText[0]->setString(temp);
    settingsText[0]->setOrigin(settingsText[0]->getGlobalBounds().width / 2, settingsText[0]->getGlobalBounds().height / 2);

    sprintf(temp, "%d", settings.effectVolume);
    settingsText[2]->setString(temp);
    settingsText[2]->setOrigin(settingsText[2]->getGlobalBounds().width / 2, settingsText[2]->getGlobalBounds().height / 2);

    if (settings.enableMouse)
    {
        settingsMenu[5]->loadTexture("resources/on.png");
    }
    else
    {
        settingsMenu[5]->loadTexture("resources/off.png");
    }

    if (settings.selectAfterUpgrade)
    {
        settingsMenu[6]->loadTexture("resources/on.png");
    }
    else
    {
        settingsMenu[6]->loadTexture("resources/off.png");
    }

    sprintf(temp, "Up: %s", keyNames[settings.leftPlayer.up]);
    settingsText[7]->setString(temp);
    sprintf(temp, "Down: %s", keyNames[settings.leftPlayer.down]);
    settingsText[8]->setString(temp);
    sprintf(temp, "Left: %s", keyNames[settings.leftPlayer.left]);
    settingsText[9]->setString(temp);
    sprintf(temp, "Right: %s", keyNames[settings.leftPlayer.right]);
    settingsText[10]->setString(temp);
    sprintf(temp, "Select: %s", keyNames[settings.leftPlayer.select]);
    settingsText[11]->setString(temp);
    sprintf(temp, "Back: %s", keyNames[settings.leftPlayer.back]);
    settingsText[12]->setString(temp);
    sprintf(temp, "Fast Forward: %s", keyNames[settings.leftPlayer.speed]);
    settingsText[13]->setString(temp);
    sprintf(temp, "Hotkey 1: %s", keyNames[settings.leftPlayer.hotkey1]);
    settingsText[14]->setString(temp);
    sprintf(temp, "Hotkey 2: %s", keyNames[settings.leftPlayer.hotkey2]);
    settingsText[15]->setString(temp);
    sprintf(temp, "Hotkey 3: %s", keyNames[settings.leftPlayer.hotkey3]);
    settingsText[16]->setString(temp);
    sprintf(temp, "Hotkey 4: %s", keyNames[settings.leftPlayer.hotkey4]);
    settingsText[17]->setString(temp);

    sprintf(temp, "Up: %s", keyNames[settings.rightPlayer.up]);
    settingsText[19]->setString(temp);
    sprintf(temp, "Down: %s", keyNames[settings.rightPlayer.down]);
    settingsText[20]->setString(temp);
    sprintf(temp, "Left: %s", keyNames[settings.rightPlayer.left]);
    settingsText[21]->setString(temp);
    sprintf(temp, "Right: %s", keyNames[settings.rightPlayer.right]);
    settingsText[22]->setString(temp);
    sprintf(temp, "Select: %s", keyNames[settings.rightPlayer.select]);
    settingsText[23]->setString(temp);
    sprintf(temp, "Back: %s", keyNames[settings.rightPlayer.back]);
    settingsText[24]->setString(temp);
    sprintf(temp, "Fast Forward: %s", keyNames[settings.rightPlayer.speed]);
    settingsText[25]->setString(temp);
    sprintf(temp, "Hotkey 1: %s", keyNames[settings.rightPlayer.hotkey1]);
    settingsText[26]->setString(temp);
    sprintf(temp, "Hotkey 2: %s", keyNames[settings.rightPlayer.hotkey2]);
    settingsText[27]->setString(temp);
    sprintf(temp, "Hotkey 3: %s", keyNames[settings.rightPlayer.hotkey3]);
    settingsText[28]->setString(temp);
    sprintf(temp, "Hotkey 4: %s", keyNames[settings.rightPlayer.hotkey4]);
    settingsText[29]->setString(temp);
}

void Menu::bindKey()
{
    bindText.setString(bindMessage);
    bindText.setOrigin(bindText.getGlobalBounds().width / 2, bindText.getGlobalBounds().height / 2);
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
        {
            if (i == sf::Keyboard::Escape)
            {
                //exit
                isBinding = false;
            }
            else
            {
                sf::Keyboard::Key * tempKey;
                int saved;
                switch(currentKey)  //was not planning ahead
                {
                    case 7:
                        tempKey = &settings.leftPlayer.up;
                        break;
                    case 8:
                        tempKey = &settings.leftPlayer.down;
                        break;
                    case 9:
                        tempKey = &settings.leftPlayer.left;
                        break;
                    case 10:
                        tempKey = &settings.leftPlayer.right;
                        break;
                    case 11:
                        tempKey = &settings.leftPlayer.select;
                        break;
                    case 12:
                        tempKey = &settings.leftPlayer.back;
                        break;
                    case 13:
                        tempKey = &settings.leftPlayer.speed;
                        break;
                    case 14:
                        tempKey = &settings.leftPlayer.hotkey1;
                        break;
                    case 15:
                        tempKey = &settings.leftPlayer.hotkey2;
                        break;
                    case 16:
                        tempKey = &settings.leftPlayer.hotkey3;
                        break;
                    case 17:
                        tempKey = &settings.leftPlayer.hotkey4;
                        break;
                    case 18:
                        tempKey = &settings.rightPlayer.up;
                        break;
                    case 19:
                        tempKey = &settings.rightPlayer.down;
                        break;
                    case 20:
                        tempKey = &settings.rightPlayer.left;
                        break;
                    case 21:
                        tempKey = &settings.rightPlayer.right;
                        break;
                    case 22:
                        tempKey = &settings.rightPlayer.select;
                        break;
                    case 23:
                        tempKey = &settings.rightPlayer.back;
                        break;
                    case 24:
                        tempKey = &settings.rightPlayer.speed;
                        break;
                    case 25:
                        tempKey = &settings.rightPlayer.hotkey1;
                        break;
                    case 26:
                        tempKey = &settings.rightPlayer.hotkey2;
                        break;
                    case 27:
                        tempKey = &settings.rightPlayer.hotkey3;
                        break;
                    case 28:
                        tempKey = &settings.rightPlayer.hotkey4;
                        break;
                }
                saved = *tempKey;
                *tempKey = (sf::Keyboard::Key)i;

                if (checkDuplicates() == false) //valid
                {
                    isBinding = false;
                    updateSettings();
                }
                else
                {
                    *tempKey = (sf::Keyboard::Key)saved;
                    sprintf(bindMessage, "Press the escape key to exit.\n\nPress the new key for %s\n\nThe %s key is already being used!", hotkeyNames[currentKey - 7], keyNames[i]);
                }
            }
        }
    }
}

bool Menu::checkDuplicates()
{
    int tempKeys[sf::Keyboard::KeyCount] = {0};

    tempKeys[settings.leftPlayer.up]++;
    tempKeys[settings.leftPlayer.down]++;
    tempKeys[settings.leftPlayer.left]++;
    tempKeys[settings.leftPlayer.right]++;
    tempKeys[settings.leftPlayer.select]++;
    tempKeys[settings.leftPlayer.back]++;
    tempKeys[settings.leftPlayer.speed]++;
    tempKeys[settings.leftPlayer.hotkey1]++;
    tempKeys[settings.leftPlayer.hotkey2]++;
    tempKeys[settings.leftPlayer.hotkey3]++;
    tempKeys[settings.leftPlayer.hotkey4]++;
    tempKeys[settings.rightPlayer.up]++;
    tempKeys[settings.rightPlayer.down]++;
    tempKeys[settings.rightPlayer.left]++;
    tempKeys[settings.rightPlayer.right]++;
    tempKeys[settings.rightPlayer.select]++;
    tempKeys[settings.rightPlayer.back]++;
    tempKeys[settings.rightPlayer.speed]++;
    tempKeys[settings.rightPlayer.hotkey1]++;
    tempKeys[settings.rightPlayer.hotkey2]++;
    tempKeys[settings.rightPlayer.hotkey3]++;
    tempKeys[settings.rightPlayer.hotkey4]++;

    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        if (tempKeys[i] > 1)
        {
            return true;
        }
    }
    return false;
}

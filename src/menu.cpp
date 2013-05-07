#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

const char * const Menu::keyNames[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Esc", "LCtrl", "LShift", "LAlt", "LOS", "RCtrl", "RShift", "RAlt", "ROS", "Menu", "[", "]", ";", ",", ".", "'", "/", "\\", "~", "=", "-", "Space", "Return", "Backspace", "Tab", "PgUp", "PgDown", "End", "Home", "Insert", "Del", "Num+", "Num-", "Num*", "Num/", "Left", "Right", "Up", "Down", "Num0", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause"};

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

    backgroundTexture.loadFromFile("resources/menuBackground.png");
    background.setTexture(&backgroundTexture);

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

    //SETTINGS
    settingsMenu.push_back(new Button());   //back button
    settingsMenu[0]->initialize(100, 50);
    settingsMenu[0]->setPosition({50, 50});
    settingsMenu[0]->loadTexture("resources/back.png");
    settingsMenu[0]->setVisible(false);
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
    for(unsigned int i = 0; i < mainMenu.size(); ++i)
    {
        if(mainMenu[i]->update(mousePos))
        {
            switch(i)
            {
                case 0: //single player
                    return 1;
                    break;
                case 1: //multi player
                    return 2;
                    break;
                case 2: //options
                    for (unsigned int a = 0; a < mainMenu.size(); ++a)
                    {
                        mainMenu[a]->setVisible(false);
                    }
                    for (unsigned int a = 0; a < settingsMenu.size(); ++a)
                    {
                        settingsMenu[a]->setVisible(true);
                    }
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
                    writeSettings();
                    break;
                case 1:
                    break;
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
        fscanf(ifp, "%d\n%d\n%d\n%d", &settings.effectVolume, &settings.musicVolume, (int*)&settings.enableMouse, (int*)&settings.selectAfterUpgrade);
        fscanf(ifp, "%d\n%d\n%d\n%d\n%d\n%d\n%d", (int*)&settings.leftPlayer.up, (int*)&settings.leftPlayer.down, (int*)&settings.leftPlayer.left, (int*)&settings.leftPlayer.right, (int*)&settings.leftPlayer.select, (int*)&settings.leftPlayer.back, (int*)&settings.leftPlayer.speed);
        fscanf(ifp, "%d\n%d\n%d\n%d", (int*)&settings.leftPlayer.hotkey1, (int*)&settings.leftPlayer.hotkey2, (int*)&settings.leftPlayer.hotkey3, (int*)&settings.leftPlayer.hotkey4);
        fscanf(ifp, "%d\n%d\n%d\n%d\n%d\n%d\n%d", (int*)&settings.rightPlayer.up, (int*)&settings.rightPlayer.down, (int*)&settings.rightPlayer.left, (int*)&settings.rightPlayer.right, (int*)&settings.rightPlayer.select, (int*)&settings.rightPlayer.back, (int*)&settings.rightPlayer.speed);
        fscanf(ifp, "%d\n%d\n%d\n%d", (int*)&settings.rightPlayer.hotkey1, (int*)&settings.rightPlayer.hotkey2, (int*)&settings.rightPlayer.hotkey3, (int*)&settings.rightPlayer.hotkey4);
    }
    else
    {
        settings.effectVolume = 5;
        settings.musicVolume = 5;
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
    }
    fclose(ifp);
}

void Menu::writeSettings()
{
    FILE * ofp = fopen("settings", "w");
    fprintf(ofp, "%d\n%d\n%d\n%d\n", settings.effectVolume, settings.musicVolume, settings.enableMouse, settings.selectAfterUpgrade);
    fprintf(ofp, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", (int)settings.leftPlayer.up, (int)settings.leftPlayer.down, (int)settings.leftPlayer.left, (int)settings.leftPlayer.right, (int)settings.leftPlayer.select, (int)settings.leftPlayer.back, (int)settings.leftPlayer.speed, (int)settings.leftPlayer.hotkey1, (int)settings.leftPlayer.hotkey2, (int)settings.leftPlayer.hotkey3, (int)settings.leftPlayer.hotkey4);
    fprintf(ofp, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", (int)settings.rightPlayer.up, (int)settings.rightPlayer.down, (int)settings.rightPlayer.left, (int)settings.rightPlayer.right, (int)settings.rightPlayer.select, (int)settings.rightPlayer.back, (int)settings.rightPlayer.speed, (int)settings.rightPlayer.hotkey1, (int)settings.rightPlayer.hotkey2, (int)settings.rightPlayer.hotkey3, (int)settings.rightPlayer.hotkey4);
    fclose(ofp);
}

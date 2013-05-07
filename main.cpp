#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstring>
#include "game.h"
#include "global.h"
#include "menu.h"

Settings settings;
Stats towerStats[3][3][3];

int main(int argc, char *argv[])
{
    settings.fastForwardSpeed = 4;      //not sure if i'll make these changable..
    settings.doubleBuffered = false;

    towerStats[3][3][3].damage = 1;

    if (argc > 1)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
            settings.doubleBuffered = !settings.doubleBuffered;
        }
    }

    sf::RenderWindow window(sf::VideoMode(XRES, YRES), "Versus", sf::Style::Close);

    Game game;
    Menu menu;
    bool inGame = false;
    bool focused = true;

    srand(time(NULL));

    window.setFramerateLimit(FPS);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::GainedFocus:
                    focused = true;
                    break;
                case sf::Event::LostFocus:
                    focused = false;
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::White);

        if(inGame)  //yay no polymorphism
        {
            if (focused)
            {
                switch(game.update(sf::Mouse::getPosition(window)))
                {
                    case 0:
                        break;
                    case 1:
                        inGame = false;
                        break;
                    case 2:
                        window.close();
                        break;
                }
            }

            game.draw(&window);
            window.display();
        }
        else
        {
            if (focused)
            {
                switch(menu.update(sf::Mouse::getPosition(window)))
                {
                    case 0:
                        break;
                    case 1:
                        inGame = true;      //TODO: have a getter in menu for game options, and access that from here to make new game
                        game.newGame(Game::right, sf::Color::Cyan, sf::Color::Magenta, sf::Color(255, 255, 0, 128), sf::Color(0, 255, 0, 128));
                        break;
                    case 2:
                        inGame = true;
                        game.newGame(Game::both, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 128), sf::Color(255, 255, 0, 128));
                        break;
                    case 10:
                        window.close();
                        break;
                }
            }

            menu.draw(&window);
            window.display();
        }
    }
    return 0;
}

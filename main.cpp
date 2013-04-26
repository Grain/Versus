#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstring>
#include "game.h"
#include "global.h"
#include "menu.h"

Settings settings;

int main(int argc, char *argv[])
{
    settings.doubleBuffered = false;
    settings.enableMouse =  true;
    settings.fastForwardSpeed = 4;

    settings.leftPlayer.up = sf::Keyboard::W;
    settings.leftPlayer.down = sf::Keyboard::S;
    settings.leftPlayer.left = sf::Keyboard::A;
    settings.leftPlayer.right = sf::Keyboard::D;
    settings.leftPlayer.select = sf::Keyboard::J;
    settings.leftPlayer.speed = sf::Keyboard::Space;

    settings.rightPlayer.up = sf::Keyboard::Up;
    settings.rightPlayer.down = sf::Keyboard::Down;
    settings.rightPlayer.left = sf::Keyboard::Left;
    settings.rightPlayer.right = sf::Keyboard::Right;
    settings.rightPlayer.select = sf::Keyboard::Numpad1;
    settings.rightPlayer.speed = sf::Keyboard::Numpad0;

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
                        game.newGame(Game::right);
                        break;
                    case 2:
                        inGame = true;
                        game.newGame(Game::both);
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

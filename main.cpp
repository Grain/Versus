#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstring>
#include "global.h"
#include "game.h"
#include "menu.h"
#include "gameaudio.h"

Settings settings;
GameAudio gameAudio;
Stats towerStats[3][4][4];
std::string descriptions[12];

int main(int argc, char *argv[])
{
    settings.fastForwardSpeed = 4;      //not changable in game hahaha
    settings.doubleBuffered = false;

    initializeStats();

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

    sf::Image icon;
    icon.loadFromFile("resources/icon.png");
    window.setIcon(256, 256, icon.getPixelsPtr());

    bool inGame = false;
    bool focused = true;

    srand(time(NULL));

    menu.updateTips();

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
                    gameAudio.resume();
                    break;
                case sf::Event::LostFocus:
                    focused = false;
                    gameAudio.pause();
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
                        menu.updateScore();
                        menu.updateTips();
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
                        game.newGame(Game::left, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 80), sf::Color(255, 255, 0, 80), 1);
                        inGame = true;
                        break;
                    case 2:
                        game.newGame(Game::left, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 80), sf::Color(255, 255, 0, 80), 2);
                        inGame = true;
                        break;
                    case 3:
                        game.newGame(Game::left, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 80), sf::Color(255, 255, 0, 80), 3);
                        inGame = true;
                        break;
                    case 4:
                        game.newGame(Game::left, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 80), sf::Color(255, 255, 0, 80), 4);
                        inGame = true;
                        break;
                    case 5:
                        inGame = true;
                        game.newGame(Game::both, sf::Color::Blue, sf::Color::Red, sf::Color(0, 255, 0, 80), sf::Color(255, 255, 0, 80), 0);
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

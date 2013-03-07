#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"
#include "global.h"
#include "menu.h"

Settings settings;

int main()
{
    sf::RenderWindow window(sf::VideoMode(XRES, YRES), "Versus", sf::Style::Close);
    Game game;
    Menu menu;

    window.setFramerateLimit(30);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    switch (menu.getState())
                    {
                        case 0: // main menu
                            // check to see if the mouse clicked a button
                            if (event.mouseButton.button == sf::Mouse::Left)
                                if (menu.checkClick(sf::Mouse::getPosition(window)) == 1)
                                {
                                    menu.setState(1);
                                }
                            break;
                        case 1: // game
                            break;
                        case 2: // options
                            break;
                        case 3: // temp
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color::White); // might be able to move this somewhere else
        if (menu.getState() == 0)
        {
            menu.update(sf::Mouse::getPosition(window));
            window.draw(menu.getBackground());
            window.draw(menu.getStartBtn());
            window.draw(menu.getOptionsBtn());
            window.draw(menu.getExitBtn());
        }
        else if (menu.getState() == 1)
        {
            game.update(sf::Mouse::getPosition(window));
            window.draw(game.getSprite());
        }

        window.display();
    }
    return 0;
}

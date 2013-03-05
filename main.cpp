#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.h"
#include "global.h"

Settings settings;

int main()
{
    sf::RenderWindow window(sf::VideoMode(XRES, YRES), "Versus", sf::Style::Close);
    Game game;

    window.setFramerateLimit(30);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.update(sf::Mouse::getPosition(window));

        window.clear(sf::Color::White);
        window.draw(game.getSprite());
        window.display();
    }

    return 0;
}

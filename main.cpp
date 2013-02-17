#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Pro", sf::Style::Close);
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

        window.clear(sf::Color::White);
        window.draw(game.get_sprite());
        window.display();
    }

    return 0;

}

#include <SFML/Graphics.hpp>

sf::Sprite * initializeGrid(sf::Color left, sf::Color right)
{
    const int boxDimensions = 40;   //each box in the grid is 40x40, not including the lines
    const int gridDimensions = 10;  //grid is 10x10 on each side
    const int middle = 3;  //3 box wide in the middle

    static sf::RenderTexture grid;

    grid.create(boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, boxDimensions * gridDimensions + gridDimensions + 1);  //TODO: check for error in creating?
    grid.clear(sf::Color::Transparent);

    sf::RectangleShape temp(sf::Vector2f(944, 411));

    temp.setFillColor(left);
    temp.setSize(sf::Vector2f(boxDimensions * gridDimensions + gridDimensions + 1, boxDimensions * gridDimensions + gridDimensions + 1));
    temp.setPosition(0, 0);
    grid.draw(temp);

    temp.setFillColor(right);
    temp.setSize(sf::Vector2f(boxDimensions * gridDimensions + gridDimensions + 1,boxDimensions * gridDimensions + gridDimensions + 1));
    temp.setPosition((gridDimensions + middle) * boxDimensions + gridDimensions + middle + 1, 0);
    grid.draw(temp);

    int i;
    for(i = 0; i <= 2 * gridDimensions + middle; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize(sf::Vector2f(1, boxDimensions * gridDimensions + gridDimensions + 1));
        temp.setPosition(i * (boxDimensions + 1), 0);
        grid.draw(temp);
    }
    for(i = 0; i <= gridDimensions; ++i)
    {
        temp.setFillColor(sf::Color::Black);
        temp.setSize(sf::Vector2f(boxDimensions * (2 * gridDimensions + middle) + gridDimensions * 2 + middle + 1, 1));
        temp.setPosition(0, i * (boxDimensions + 1));
        grid.draw(temp);
    }

    grid.display();
    return new sf::Sprite(grid.getTexture());  //memory leak D:
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 576), "Pro", sf::Style::Close);

    window.setFramerateLimit(30);

    sf::Sprite * field = initializeGrid(sf::Color::Yellow, sf::Color::Green);
    field->setPosition(40, 0);

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
        window.draw(*field);
        window.display();
    }

    return 0;

}

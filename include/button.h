#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
        //ctor/dtor
        Button();
        virtual ~Button();
        //getters
        sf::Vector2f getSize();
        sf::Vector2f getPosition();
        bool getVisible();
        //setters
        void setPosition(sf::Vector2f);
        void setVisible(bool);
        //functions
        void initialize(int, int);
        void loadTexture(std::string);
        bool update(sf::Vector2i);
        void draw(sf::RenderTarget*);
    protected:
    private:
        //functions
        bool inButton(sf::Vector2i);

        sf::RectangleShape rect;
        sf::Texture normal, mouseOver, mouseDown;
        bool visible;
        bool prevState; //state of mouse button in last update
        bool downed;    //whether the mouse was downed on the button
};

#endif // BUTTON_H

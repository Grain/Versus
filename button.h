#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
private:
    //vars
    int x, y, w, h;
    sf::Color bgColor;
    sf::Color fgColor;
    //function pointer
    void *onClick();     //can you make it so a click = mouseDown on button then mouseUp on button
public:
    Button();
    virtual ~Button();

    //setters
    void setWidth(int i);
    void setHeight(int i);
    void setPos(int a, int b);

};

#endif // BUTTON_H

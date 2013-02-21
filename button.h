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

    //getters
    inline int getWidth();
    inline int getHeight();
    inline int getTop();
    inline int getLeft();
    inline int getRight();
    inline int getBottom();

    //setters
    void setWidth(int);
    void setHeight(int);
    void setDim(int,int);
    void setPos(int, int);
    void setColor(sf::Color, sf::Color);
};

#endif // BUTTON_H

#ifndef BTN_H
#define BTN_H

#include <Drawable.h>
#include "global.h"


class Btn : public Drawable
{
    public:
        Btn();
        virtual ~Btn();
        //getters
        sf::Vector2i getCoordinates();
        //setters
        void setCoordinates(sf::Vector2i);
        //functions
        void update(); // don't think this is needed for buttons
    protected:
    private:
        //functions
        sf::Sprite initializeBtns(int);
        //vars
        sf::Vector2i coordinates;
        sf::Sprite exitBtn;
        sf::Sprite startBtn;
        sf::Sprite optionBtn;

};

#endif // BTN_H


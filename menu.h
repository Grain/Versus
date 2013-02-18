#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Button
{
    int x,y, w,h;
    sf::Color bgColor;
    sf::Color fgColor;


public:
    Button();
    virtual ~Button();

    void setWidth(int);
    void setHeight(int);
    void setPos(int,int);

    //function pointer
    int *onClick();
};


class Menu      //Menu will be similar to Game, will have RenderTexture that everything gets rendered on, then gets converted into sprite for drawing on the window
{
    public:
        Menu();
        virtual ~Menu();

        vector<Button*> buttons;

        void newButton(string, void*func())
        void addButton(Button*);
        void delButton(Button*);
        void clrButton();
    protected:
    private:
};


#endif // MENU_H

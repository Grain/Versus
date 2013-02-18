#include "menu.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Menu::Menu()
{
    //ctor
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Menu::~Menu()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/
void Menu::newButton(string text, void (*func)())
{
    Button *btn = new Button();
    btn->setWidth(100);
    btn->setHeight(50);
    buttons.push_back(btn);
}

void Menu::addButton(Button*b)
{
    buttons.push_back(b);
}

void Menu::deleteButton(Button*b)
{
    int i;
    for (i = 0; i < buttons.size(); i++)
    {
        if (&buttons[i] == b)
        {
            delete buttons[i];
            buttons.erase(buttons.begin()+i);
        }
    }
}

void Menu::clearButtons()
{
    while (buttons.size() > 0)
    {
        delete buttons[0];
        buttons.erase(buttons.begin());
    }
}
